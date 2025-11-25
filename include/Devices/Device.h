/*
 * File: include/Devices/Device.h
 * Description: Abstract Base Class for all IoT devices.
 * Standard: C++98
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <iostream>

class Device {
protected:
    int id;                 // Cihaz ID
    std::string name;       // Cihaz Adi (Marka/Model)
    bool isPoweredOn;       // Acik/Kapali Durumu
    bool isActive;          // Arizali/Saglam Durumu

public:
    // Constructor
    Device(int deviceId, const std::string& deviceName) 
        : id(deviceId), name(deviceName), isPoweredOn(false), isActive(true) {
    }

    // Virtual Destructor (Cok onemli)
    virtual ~Device() {}

    // Cihazi Acar
    virtual void turnOn() {
        if (!isActive) {
            std::cout << "[Error] " << name << " is broken! Cannot turn on." << std::endl;
            return;
        }
        isPoweredOn = true;
        std::cout << name << " (ID: " << id << ") is now ON." << std::endl;
    }

    // Cihazi Kapatir
    virtual void turnOff() {
        isPoweredOn = false;
        std::cout << name << " (ID: " << id << ") is now OFF." << std::endl;
    }

    // Prototype Pattern icin gerekli (Kopyalama)
    virtual Device* clone() const = 0;

    // Durum Yazdirma (Her cihaz kendi ozel durumunu yazar)
    virtual void printStatus() const = 0;

    // Getter Metodlar
    int getID() const { return id; }
    std::string getName() const { return name; }
    bool getPowerState() const { return isPoweredOn; }
};

#endif // DEVICE_H
