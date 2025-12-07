#ifndef TV_H
#define TV_H

#include "Device.h"

class TV : public Device {
public:
    virtual void setChannel(int ch) = 0;
protected:
    int currentChannel;
};

#endif
