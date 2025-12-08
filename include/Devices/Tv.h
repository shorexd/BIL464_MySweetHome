#ifndef TV_H
#define TV_H

#include "Device.h"

class TV : public Device {
protected:
    int currentChannel;
public:
    TV() : currentChannel(1) {}
    virtual void setChannel(int ch) = 0;
};

#endif