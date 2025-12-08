#include "Devices/SamsungFactory.h"

Device* SamsungFactory::createTV() {
    return new SamsungTV();
}
