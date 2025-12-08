/**
 * DOSYA: include/Devices/Device.h
 * DUZELTME: Prototype (clone) ve Kimlik (id, name) eklendi.
 */
#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <iostream>

class Device {
protected:
    int id;
    std::string name;
    bool isOn;

public:
    Device() : id(0), name("Unknown"), isOn(false) {}
    virtual ~Device() {}

    // Temel Fonksiyonlar
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;

    // Getters & Setters
    void setID(int newID) { id = newID; }
    int getID() const { return id; }
    
    void setName(const std::string& n) { name = n; }
    std::string getName() const { return name; }

    // --- PROTOTYPE PATTERN (Kritik) ---
    // Yunus'un kopyalama yapabilmesi icin bu sart!
    virtual Device* clone() const = 0;
};

#endif