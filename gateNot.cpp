#include "gateNot.h"

int gateNot::getOutput() const{
    
    if(iPins[0]->getOutput() == 0){
        return 1;
    }
    return 0;
}