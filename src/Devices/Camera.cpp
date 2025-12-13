#include "Devices/Camera.h"
#include <iostream>

Camera::Camera() {}

Camera::~Camera() {}

void Camera::attach(IObserver* observer) {
    observers.push_back(observer);
}

void Camera::detach(IObserver* /*observer*/) {
    // Gercek projede listeden cikarma yapilir
    // Su anlik implementasyon bos oldugu icin parametre ismini kaldirdik
}

void Camera::notify(const std::string& eventType) {
    for (size_t i = 0; i < observers.size(); ++i) {
        observers[i]->update(eventType);
    }
}

void Camera::detectMotion() {
    std::cout << "[Camera] HAREKET ALGILANDI!\n";
    notify("MOTION_DETECTED");
}

std::string Camera::getType() const {
    return "Camera";
}