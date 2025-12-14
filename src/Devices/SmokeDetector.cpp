#include "Devices/SmokeDetector.h"
#include <iostream>

SmokeDetector::SmokeDetector() {
    this->name = "Duman/Gaz Dedektoru";
    this->isOn = true;
}

SmokeDetector::~SmokeDetector() {}

void SmokeDetector::attach(IObserver* observer) {
    observers.push_back(observer);
}

void SmokeDetector::detach(IObserver* /*observer*/) {}

void SmokeDetector::notify(const std::string& eventType) {
    for (size_t i = 0; i < observers.size(); ++i) {
        observers[i]->update(eventType);
    }
}

// Device Fonksiyonlari
void SmokeDetector::turnOn() {
    isOn = true; 
    std::cout << "[Detector] ID:" << id << " Aktif." << std::endl;
}

void SmokeDetector::turnOff() {
    std::cout << "[Detector] ID:" << id << " Kapatilamaz (Guvenlik Geregi)." << std::endl;
}

Device* SmokeDetector::clone() const {
    return new SmokeDetector(*this);
}

void SmokeDetector::detectSmoke() {
    std::cout << "[SmokeGasDetector " << id << "] DUMAN/GAZ ALGILANDI!\n";
    notify("DANGER_DETECTED");
}

std::string SmokeDetector::getType() const {
    return "SmokeGasDetector";
}