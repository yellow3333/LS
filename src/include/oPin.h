#ifndef _OPIN_
#define _OPIN_
#include "Device.h"

class oPin : public Device{
public:
    int getOutput() const override;
};

#endif