#include "gateAND.h"

int gateAND::getOutput() const{
    for(auto& pin : iPins){
        if(pin->getOutput() == 0)return 0;
    }
    return 1;
}