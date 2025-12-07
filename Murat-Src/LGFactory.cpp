#include "../murat-devices/LGFactory.h"

Device* LGFactory::createTV() {
    return new LGTV();
}
