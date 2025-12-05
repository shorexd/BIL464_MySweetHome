#include "../../include/Devices/Camera.h"
#include <iostream>

Camera::Camera() {}

Camera::~Camera() {}

void Camera::attach(IObserver* observer) {
    observers.push_back(observer);
}

void Camera::detach(IObserver* observer) {
    // Listeden cikarma mantigi (Simdilik bos kalabilir)
}

void Camera::notify(const std::string& event_type) {
    for (size_t i = 0; i < observers.size(); ++i) {
        observers[i]->update(event_type);
    }
}

void Camera::detectMotion() {
    std::cout << "[Camera] Hareket algilandi! Sinyal gonderiliyor..." << std::endl;
    notify("MOTION_DETECTED");
}