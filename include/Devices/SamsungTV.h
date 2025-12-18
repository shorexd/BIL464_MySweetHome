#ifndef SAMSUNG_TV_H
#define SAMSUNG_TV_H

#include "TV.h"

class SamsungTV : public TV {
public:
    SamsungTV();
    void turnOn();
    void turnOff();
    void setChannel(int ch);
    
    // Prototype Clone Eklendi
    Device* clone() const;
};

#endif