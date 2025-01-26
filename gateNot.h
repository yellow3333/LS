#ifndef _GATENOT_
#define _GATENOT_
#include "Device.h"

class gateNot : public Device{
public:
    int getOutput() const override;
};

#endif