#include "Devices/SmokeDetector.h"
#include <iostream>

SmokeDetector::SmokeDetector() {}

SmokeDetector::~SmokeDetector() {}

void SmokeDetector::attach(IObserver* observer) {
    observers.push_back(observer);
}

void SmokeDetector::detach(IObserver* /*observer*/) {
    // Parametre kullanilmadigi icin ismi kaldirildi (Warning fix)
}

void SmokeDetector::notify(const std::string& eventType) {
    for (size_t i = 0; i < observers.size(); ++i) {
        observers[i]->update(eventType);
    }
}

void SmokeDetector::detectSmoke() {
    std::cout << "[SmokeDetector] DUMAN ALGILANDI!\n";
    notify("DANGER_DETECTED");
}

std::string SmokeDetector::getType() const {
    return "SmokeDetector";
}