#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include "Device.h"
#include "TVConfig.h" // Config yapisini tanittik

class DeviceFactory {
public:
    // UML & LLR-03: Config parametresi eklendi
    virtual Device* createTV(const TVConfig& config) = 0;
    
    virtual ~DeviceFactory() {}
};

#endif