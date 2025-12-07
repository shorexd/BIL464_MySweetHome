#include "../murat-devices/SamsungFactory.h"

Device* SamsungFactory::createTV() {
    return new SamsungTV();
}
