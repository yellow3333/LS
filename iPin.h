#ifndef _IPIN_
#define _IPIN_
#include "Device.h"

class iPin : public Device{
public:
    int getOutput() const override;
};

#endif