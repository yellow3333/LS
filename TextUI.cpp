#include "TextUI.h"
#include "LogicSimulator.h"

using namespace std;

int inputDigit(){
    string str;
    cin >> str;
    if(str.length()==1 && isdigit(str[0])) return int(str[0]) - 48; // ascii '0' = 48 
    else return -1;
}

int inputServe(int serve, int iPinID = 0){
    // serve : command is 0, input pin is 1
    string  message[2] = {"Command:", "Please key in the value of input pin "},
            errorMessage[2] = {"command must be 1 to 4\n\n", "The value of input pin must be 0/1\n"};
    int input;
    while(true){
        cout << message[serve];

        if(serve == 1) printf("%d: ",iPinID+1);
        input = inputDigit();
        if(serve == 0){
            if(input > 0 && input < 5) return input;
        }else{
            if(input == 0 || input == 1) return input;
        }

        cout << errorMessage[serve];
    }
    
    
}

bool TextUI::displayMenu(){
    vector<string> options ({"Load logic circuit file", "Simulation", "Display truth table", "Exit"});

    for(int i = 1; i <= options.size();i++)
        printf("%d. %s\n",i,options[i-1].c_str());
    
    return processCommand();
}

bool TextUI::processCommand(){

    int command;
    command = inputServe(0); // 0 is command serve
    if(command == 1){ // Load logic circuit file
        string path;
        printf("Please key in a file path : ");
        cin >> path;
        loadCompleted = ls->load(path);
        if(!loadCompleted) 
            printf("File not found or file format error!!\n");
    }else if(command == 4){
        delete ls;
        printf("Goodbye, thanks for using LS.");
        return false;
    }else if(loadCompleted){// check the file is loaded
        if(command == 2){ // Simulation
            vector<int> pins;
            for(int i = 0; i < ls->getInPinSize(); i++) pins.push_back(inputServe(1,i));// 1 is input pin
            ls->getSimulationResult(pins);
        }else{ // Display truth table
            ls->getTruthTable();
        }
    }else {
        printf("Please load an lcf file, before using this operation.\n");
    }
    cout<<"\n";
    
    return true;
}


