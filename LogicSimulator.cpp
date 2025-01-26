#include "LogicSimulator.h"
#include "Device.h"
#include "iPin.h"
#include "gateAND.h"
#include "gateOR.h"
#include "gateNot.h"
#include "oPin.h"


using namespace std;

int NI=0, NG, NO = 0;

LogicSimulator::LogicSimulator() {}

LogicSimulator::~LogicSimulator() {

    for (Device* pin : iPins) {
        delete pin;
    }
    iPins.clear();

    for (Device* gate : circuit) {
        delete gate;
    }
    circuit.clear(); 
    
    for (Device* pin : oPins) {
        delete pin;
    }
    oPins.clear();
}


void out_talbe_head(){
    for(int j = 0; j < 3; j++){
        for(int i = 0; i < NI; i++){
            if(j == 0)cout << "i ";
            else if(j == 1) cout << i+1 <<" ";
            else cout<< "--";
        }
        if(j == 2)cout << "+";
        else cout << "|";
        for(int i = 0; i < NO; i++){
            if(j == 0)cout << " o";
            else if(j == 1) cout <<" " << i+1;
            else cout<< "--";
        }
        cout<<"\n";
    }
    return ;
}

void LogicSimulator::out_table(const vector<int>& pins) const{

    for(int i = 0; i < NI; i++){
        cout<< pins[i]<<" ";
        iPins[i]->addinputPins(pins[i]);
    } 
    cout << "|";

    for(int i = 0; i < NO; i++){
        cout <<" " << oPins[i]->getOutput() ;
    } 
    cout<<"\n";
    return ;
}

void LogicSimulator::getSimulationResult(const vector<int>& pins){
    printf("Simulation Result: \n");
    out_talbe_head();
    out_table(pins);
    
    return ;
}

void LogicSimulator::getTruthTable(){
    int temp;
    printf("Truth table: \n");
    out_talbe_head();

    // decimal -> binary
    for(int i = 0; i < pow(2,NI); i++){
        vector<int> pins(NI,0);
        temp = i;
        for(int j=NI-1;j>=0;j--){
                pins[j] = temp%2;
                temp/=2;
        }
        out_table(pins);
    }
    
    return ;
}

int LogicSimulator::get_iPin_size() const{
    return iPins.size();
}

Device* which_gate(int v){
    if(v == 1) return new gateAND;
    else if(v == 2) return new gateOR;
    else return new gateNot;
}

bool isLCFFile(const string& path) {
    if (path.length() >= 4) {
        return path.substr(path.length() - 4) == ".lcf"; 
    }
    return false;
}

bool LogicSimulator::load(const string& path){
    ifstream in;
    in.open(path);
    if(in.fail() || !isLCFFile(path)) return false;
    
    in >> NI;
    in >> NG;
    
    iPins.resize(NI);
    for (int i = 0; i < NI; ++i) {
        iPins[i] = new iPin;
    }
    
    circuit.resize(NG);
    vector<vector<float>> input(NG);

    // check circuit gate & reocrd input 
    float temp;
    for(int i = 0; i < NG; i++ ){
        while(true){
            in >> temp;
            if(temp == 0) break;
            if(circuit[i] == nullptr) circuit[i]= which_gate(int(temp));
            else input[i].push_back(temp);
        }
    }
    int index;
    vector<bool> connect(NG,false);

    // gate add input Pins
    for(int i = 0; i < NG; i++ ){
        for(int j = 0; j< input[i].size(); j++){
            if(input[i][j]<0){
                index = int(input[i][j])*(-1)-1;
                circuit[i]->addinputPins(iPins[index]);
            }
            else{
                index = int(input[i][j]*10)/10-1;
                circuit[i]->addinputPins(circuit[index]);
                connect[index] = true;
            }
        }
    }

    // gate is't other input -> output
    for(int i = 0; i < connect.size();i++ ){
        if(connect[i] == false){
            NO ++;
            oPins.push_back(new oPin);
            oPins[i]->addinputPins(circuit[i]);
        }
    }
    
    printf("Circuit: %d input pins, %d output pins and %d gates\n", NI, NO, NG);
    in.close();
    return true;
}
