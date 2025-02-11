#include "./include/gateOR.h"

int gateOR::getOutput() const{

    for(auto& pin : iPins){
        if(pin->getOutput() == 1)
            return 1;
    }
    return 0;
}