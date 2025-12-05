#include "../../include/Devices/SmokeDetector.h"
#include <iostream>

SmokeDetector::SmokeDetector() {}

SmokeDetector::~SmokeDetector() {}

void SmokeDetector::attach(IObserver* observer) {
    observers.push_back(observer);
}

void SmokeDetector::detach(IObserver* observer) {
    // Implementation not needed for basic scenario
}

void SmokeDetector::notify(const std::string& event_type) {
    for (size_t i = 0; i < observers.size(); ++i) {
        observers[i]->update(event_type);
    }
}

void SmokeDetector::detectSmoke() {
    std::cout << "[SmokeDetector] Duman/Gaz algilandi! Sinyal gonderiliyor..." << std::endl;
    notify("DANGER_DETECTED");
}