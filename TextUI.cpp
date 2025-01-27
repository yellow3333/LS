#include "TextUI.h"
#include "LogicSimulator.h"

using namespace std;

LogicSimulator ls;
bool load_completed = false;

int input_digit(){
    string s;
    cin >> s;
    if(s.length()==1 && isdigit(s[0])) return int(s[0]) - 48; // ascii '0' = 48 
    else return -1;
}

int input_command(){
    while (true){
        printf("Command:");
        int in = input_digit();    
        if(in>0 && in<5)return in;
        
        printf("command must be 1 to 4\n\n");
    }
}

int input_pin(int i){
    
    while (true)
    {
        printf("Please key in the value of input pin %d: ",i+1);
        int in = input_digit();
        if(in==0 || in==1) return in;

        printf("The value of input pin must be 0/1\n");
    }
}

void TextUI::displayMenu(){
    vector<string> options ({"Load logic circuit file", "Simulation", "Display truth table", "Exit"});

    for(int i = 1; i<=options.size();i++)
        printf("%d. %s\n",i,options[i-1].c_str());

    processCommand();
}

void out_talbe_head(){
    int NI = ls.get_iPin_size(), NO = ls.get_oPin_size();
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

void out_table(vector<int> pins,vector<int>& ans){
    int NI = ls.get_iPin_size(), NO = ls.get_oPin_size();
    for(int i = 0; i < NI; i++){
        cout<< pins[i]<<" ";
    } 
    cout << "|";

    for(int i = 0; i < NO; i++){
        cout <<" " << ans[i] ;
    } 
    cout<<"\n";
    return ;
}


void TextUI::processCommand(){

    int command;
    command = input_command();
    if(command == 1){ // Load logic circuit file
        string path;
        printf("Please key in a file path : ");
        cin >> path;
        load_completed = ls.load(path);
        if(!load_completed) 
            printf("File not found or file format error!!\n");
    }else if(command == 4){
        ls.~LogicSimulator();
        printf("Goodbye, thanks for using LS.");
        exit(EXIT_SUCCESS) ;
    }else if(load_completed){// check the file is loaded
        if(command == 2){ // Simulation
        
            vector<int> pins, ans;
            for(int i = 0; i < ls.get_iPin_size(); i++) pins.push_back(input_pin(i));
            ans = ls.getSimulationResult(pins);

            printf("Simulation Result: \n");
            out_talbe_head();
            out_table(pins, ans);


        }else{ // Display truth table
            vector<vector<int>> ans;
            ans = ls.getTruthTable();

            printf("Truth table: \n");
            out_talbe_head();
            int temp, NI = ls.get_iPin_size();

            for(int i = 0; i < pow(2,NI); i++){
                vector<int> pins(NI,0);
                temp = i;
                for(int j=NI-1;j>=0;j--){
                        pins[j] = temp%2;
                        temp/=2;
                }
                out_table(pins, ans[i]);
            }
        }
    }else {
        printf("Please load an lcf file, before using this operation.\n");
    }
    cout<<"\n";

    
}


