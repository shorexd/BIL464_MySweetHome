#include "Devices/SamsungTV.h" // Yol duzeltildi
#include <iostream>

SamsungTV::SamsungTV() {
    name = "Samsung Smart TV"; // Isim atamasi
    currentChannel = 1;
}

void SamsungTV::turnOn() {
    isOn = true;
    std::cout << "[SamsungTV] " << name << " (ID: " << id << ") Turning ON." << std::endl;
}

void SamsungTV::turnOff() {
    isOn = false;
    std::cout << "[SamsungTV] Turning OFF." << std::endl;
}

void SamsungTV::setChannel(int ch) {
    currentChannel = ch;
    std::cout << "[SamsungTV] Channel set to: " << currentChannel << std::endl;
}

// Prototype Implementation
Device* SamsungTV::clone() const {
    return new SamsungTV(*this); // Copy Constructor cagirir
}