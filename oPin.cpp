#include "oPin.h"

int oPin::getOutput() const{
    return iPins[0]->getOutput();
}