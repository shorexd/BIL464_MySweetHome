#include "Devices/LGFactory.h"
#include "Devices/LGTV.h"
#include <iostream>

Device* LGFactory::createTV(const TVConfig& config) {
    // LLR-04: Model dogrulama
    if (config.model.empty()) {
        std::cerr << "[Error] LGFactory: Model ismi bos olamaz!" << std::endl;
        return 0;
    }

    LGTV* tv = new LGTV();
    // LLR-03: Konfigurasyonu uygula
    tv->setName("LG " + config.model);
    tv->setBrand("LG");
    tv->setResolution(config.resolution);
    tv->setFPS(config.fps);

    return tv;
}