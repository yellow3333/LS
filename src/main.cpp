#include <iostream>
#include "./include/TextUI.h"
using namespace std;

int main(){
    TextUI ui;
    while(true){
        ui.displayMenu();
        if(!ui.processCommand()) break;
    }
}

// g++ main.cpp TextUI.cpp LogicSimulator.cpp Device.cpp gateAND.cpp gateNot.cpp gateOR.cpp iPin.cpp oPin.cpp -o main
// main.exe
// C:\Users\Ken\Code\HW\src\testLcf\file1.lcf
// C:\Users\Ken\Code\HW\src\testLcf\test.lcf