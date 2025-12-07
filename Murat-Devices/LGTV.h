#ifndef LG_TV_H
#define LG_TV_H

#include "TV.h"

class LGTV : public TV {
public:
    LGTV();
    void turnOn();
    void turnOff();
    void setChannel(int ch);
};

#endif
