#ifndef _GATEAND_
#define _GATEAND_
#include "Device.h"

class gateAND : public Device{
public:
    int getOutput() const override;
};

#endif