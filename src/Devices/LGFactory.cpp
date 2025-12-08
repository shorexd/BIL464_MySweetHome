#include "Devices/LGFactory.h"

Device* LGFactory::createTV() {
    return new LGTV();
}
