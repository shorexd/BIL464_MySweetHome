#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <iostream>

class Device {
protected:
    int id;
    std::string name;
    bool isOn;
    bool isBroken; // YENI: Ariza Durumu

public:
    Device() : id(0), name("Unknown"), isOn(false), isBroken(false) {}
    virtual ~Device() {}

    // Temel Fonksiyonlar
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;

    // Getters & Setters
    void setID(int newID) { id = newID; }
    int getID() const { return id; }
    
    void setName(const std::string& n) { name = n; }
    std::string getName() const { return name; }

    // Listeleme ve kontrol icin gerekli
    virtual bool getPowerState() const { return isOn; }

    // --- ARIZA YONETIMI (YENI) ---
    void setBroken(bool status) { 
        isBroken = status; 
        if(isBroken) isOn = false; // Arizalaninca otomatik kapat
    }
    bool getBroken() const { return isBroken; }

    // --- PROTOTYPE PATTERN ---
    virtual Device* clone() const = 0;
};

#endif