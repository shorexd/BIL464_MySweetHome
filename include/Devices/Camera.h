#ifndef CAMERA_H
#define CAMERA_H

#include "Logic/Observer.h"
#include "Device.h" // <--- EKLENDI
#include <string>
#include <vector>

// COKLU KALITIM: Hem yayin yapiyor (Subject) hem de bir Cihaz (Device)
class Camera : public ISubject, public Device {
private:
    std::vector<IObserver*> observers;

public:
    Camera();
    virtual ~Camera();

    // ISubject Arayuzu
    void attach(IObserver* observer);
    void detach(IObserver* observer);
    void notify(const std::string& eventType);

    // Device Arayuzu (Abstract oldugu icin doldurmak zorundayiz)
    void turnOn();
    void turnOff();
    Device* clone() const; // Prototype icin

    // Kendi Fonksiyonlari
    void detectMotion();
    std::string getType() const;
};

#endif