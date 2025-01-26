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
            vector<int> pins;
            for(int i = 0; i < ls.get_iPin_size(); i++) pins.push_back(input_pin(i));
            ls.getSimulationResult(pins);
        }else{ // Display truth table
            ls.getTruthTable();
        }
    }else {
        printf("Please load an lcf file, before using this operation.\n");
    }
    cout<<"\n";

    
}


