#include "./include/LogicSimulator.h"
#include "./include/Device.h"
#include "./include/iPin.h"
#include "./include/gateAND.h"
#include "./include/gateOR.h"
#include "./include/gateNot.h"
#include "./include/oPin.h"

using namespace std;

LogicSimulator::LogicSimulator() : numOfIn(0), numOfGate(0), numOfOut(0) {
}

LogicSimulator::~LogicSimulator() {
    clearLogic();
}

void LogicSimulator::clearLogic(){
    for (Device* pin : iPins) {
        delete pin;
    }
    iPins.clear();
    numOfIn = 0;

    for (Device* gate : circuit) {
        delete gate;
    }
    circuit.clear(); 
    numOfGate = 0;
    
    for (Device* pin : oPins) {
        delete pin;
    }
    oPins.clear();
    numOfOut = 0;
    
}


void LogicSimulator::outTalbeHead()const{
    for(int j = 0; j < 3; j++){
        for(int i = 0; i < numOfIn; i++){
            if(j == 0)cout << "i ";
            else if(j == 1) cout << i+1 <<" ";
            else cout<< "--";
        }
        if(j == 2)cout << "+";
        else cout << "|";
        for(int i = 0; i < numOfOut; i++){
            if(j == 0)cout << " o";
            else if(j == 1) cout <<" " << i+1;
            else cout<< "--";
        }
        cout<<"\n";
    }
    return ;
}

void LogicSimulator::outTableItem(const vector<int>& pins) const{

    for(int i = 0; i < numOfIn; i++){
        cout<< pins[i]<<" ";
        iPins[i]->addinputPins(pins[i]);
    } 
    cout << "|";

    for(int i = 0; i < numOfOut; i++){
        cout <<" " << oPins[i]->getOutput() ;
    } 
    cout<<"\n";
    return ;
}

void LogicSimulator::getSimulationResult(const vector<int>& pins){
    cout << "Simulation Result: \n";
    outTalbeHead();
    outTableItem(pins);
    
    return ;
}

void LogicSimulator::getTruthTable(){
    int temp;
    cout << "Truth table: \n";
    outTalbeHead();

    // decimal -> binary
    for(int i = 0; i < pow(2,numOfIn); i++){
        vector<int> pins(numOfIn,0);
        temp = i;
        for(int j = numOfIn-1; j >= 0; j--){
                pins[j] = temp%2;
                temp/=2;
        }
        outTableItem(pins);
    }
    
    return ;
}

int LogicSimulator::getInPinSize(){
    return iPins.size();
}

Device* which_gate(int gateID){
    if(gateID == 1) return new gateAND;
    else if(gateID == 2) return new gateOR;
    else return new gateNot;
}

bool isLcfFile(const string& path){
    if (path.length() >= 4) {
        return path.substr(path.length() - 4) == ".lcf"; 
    }
    return false;
}

bool LogicSimulator::load(const string& path){
    // Delete previous file
    clearLogic();
    
    ifstream in(path);
    if(!in.is_open()||!isLcfFile(path)) return false;
    
    in >> numOfIn;
    in >> numOfGate;
    
    iPins.resize(numOfIn);
    for (int i = 0; i < numOfIn; ++i) {
        iPins[i] = new iPin;
    }
    circuit.resize(numOfGate);
    vector<vector<float>> input(numOfGate);

    // check circuit gate & reocrd input 
    float temp;
    for(int i = 0; i < numOfGate; i++ ){
        while(true){
            in >> temp;
            if(temp == 0) break;
            if(circuit[i] == nullptr) circuit[i] = which_gate(int(temp));
            else input[i].push_back(temp);
        }
    }

    int index;
    vector<bool> connect(numOfGate,false);

    // gate add input Pins
    for(int i = 0; i < numOfGate; i++ ){
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

    numOfOut = 0;
    // gate is't other's input -> output pin
    for(int i = 0; i < connect.size();i++ ){
        if(connect[i] == false){
            numOfOut ++;
            oPins.push_back(new oPin);
            oPins[numOfOut-1]->addinputPins(circuit[i]);
        }
    }
    cout<< "Circuit: "<< numOfIn << " input pins, "<< numOfOut <<" output pins and " << numOfGate << " gates\n";
    in.close();
    return true;
}
