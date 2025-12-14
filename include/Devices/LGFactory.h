#ifndef LG_FACTORY_H
#define LG_FACTORY_H
#include "DeviceFactory.h"

class LGFactory : public DeviceFactory {
public:
    Device* createTV(const TVConfig& config); // Parametre eklendi
};
#endif