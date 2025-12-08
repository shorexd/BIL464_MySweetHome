#ifndef SAMSUNG_FACTORY_H
#define SAMSUNG_FACTORY_H

#include "DeviceFactory.h"

class SamsungFactory : public DeviceFactory {
public:
    Device* createTV();
};

#endif
