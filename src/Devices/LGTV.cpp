#include "Devices/LGTV.h"
#include <iostream>

LGTV::LGTV() {
    name = "LG OLED TV";
    currentChannel = 1;
}

void LGTV::turnOn() {
    isOn = true;
    std::cout << "[LGTV] " << name << " (ID: " << id << ") Turning ON." << std::endl;
}

void LGTV::turnOff() {
    isOn = false;
    std::cout << "[LGTV] Turning OFF." << std::endl;
}

void LGTV::setChannel(int ch) {
    currentChannel = ch;
    std::cout << "[LGTV] Channel set to: " << currentChannel << std::endl;
}

// Prototype Implementation
Device* LGTV::clone() const {
    return new LGTV(*this);
}