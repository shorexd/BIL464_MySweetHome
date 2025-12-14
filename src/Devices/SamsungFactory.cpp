#include "Devices/SamsungFactory.h"
#include "Devices/SamsungTV.h"
#include <iostream>

Device* SamsungFactory::createTV(const TVConfig& config) {
    // LLR-04: Model dogrulama (Validation)
    if (config.model.empty() || config.model.length() < 3) {
        std::cerr << "[Error] SamsungFactory: Gecersiz model ismi! (LLR-04)" << std::endl;
        return 0; // Gecersizse nesne uretme
    }

    SamsungTV* tv = new SamsungTV();
    // LLR-03: Baslangic durumlarini set et
    tv->setName("Samsung " + config.model);
    tv->setBrand("Samsung");
    tv->setResolution(config.resolution);
    tv->setFPS(config.fps);
    
    return tv;
}