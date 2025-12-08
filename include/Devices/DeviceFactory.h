#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include "Device.h"
#include "SamsungTV.h"
#include "LGTV.h"

class DeviceFactory {
public:
    virtual Device* createTV() = 0;
    virtual ~DeviceFactory() {}
};

#endif
