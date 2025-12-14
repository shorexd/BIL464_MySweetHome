#include "Devices/Camera.h"
#include <iostream>

Camera::Camera() {
    this->name = "Guvenlik Kamerasi"; // Device'dan gelen name
    this->isOn = true; // Kameralar hep acik (LLR geregi)
}

Camera::~Camera() {}

void Camera::attach(IObserver* observer) {
    observers.push_back(observer);
}

void Camera::detach(IObserver* /*observer*/) {}

void Camera::notify(const std::string& eventType) {
    for (size_t i = 0; i < observers.size(); ++i) {
        observers[i]->update(eventType);
    }
}

// Device Fonksiyonlari
void Camera::turnOn() {
    isOn = true;
    std::cout << "[Camera] ID:" << id << " Aktif." << std::endl;
}

void Camera::turnOff() {
    // Senaryo geregi kameralar kapanmaz ama fonksiyonu bos da olsa yazmaliyiz
    std::cout << "[Camera] ID:" << id << " Kapatilamaz (Guvenlik Geregi)." << std::endl;
}

Device* Camera::clone() const {
    return new Camera(*this);
}

void Camera::detectMotion() {
    std::cout << "[Camera " << id << "] HAREKET ALGILANDI!\n";
    notify("MOTION_DETECTED");
}

std::string Camera::getType() const {
    return "Camera";
}