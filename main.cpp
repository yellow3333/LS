#include <iostream>
#include "TextUI.h"
using namespace std;

int main(){
    TextUI ui;
    while(true) ui.displayMenu();
}

// g++ main.cpp TextUI.cpp LogicSimulator.cpp Device.cpp gateAND.cpp gateNot.cpp gateOR.cpp iPin.cpp oPin.cpp -o main
// main.exe
// C:\Users\Ken\OneDrive\桌面\HW\file1.lcf