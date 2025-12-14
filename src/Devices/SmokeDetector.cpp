#include "Devices/SmokeDetector.h"
#include <iostream>

SmokeDetector::SmokeDetector() {}

SmokeDetector::~SmokeDetector() {}

void SmokeDetector::attach(IObserver* observer) {
    observers.push_back(observer);
}

void SmokeDetector::detach(IObserver* /*observer*/) {
    // Bos implementasyon
}

void SmokeDetector::notify(const std::string& eventType) {
    for (size_t i = 0; i < observers.size(); ++i) {
        observers[i]->update(eventType);
    }
}

void SmokeDetector::detectSmoke() {
    // LLR-04: SmokeGasDetector olarak gorunmeli
    std::cout << "[SmokeGasDetector] DUMAN/GAZ ALGILANDI!\n";
    notify("DANGER_DETECTED");
}

std::string SmokeDetector::getType() const {
    return "SmokeGasDetector"; // LLR uyumlulugu icin isim guncellendi
}