#ifndef _GATEOR_
#define _GATEOR_
#include "Device.h"

class gateOR : public Device{
public:
    int getOutput() const override;
};

#endif
