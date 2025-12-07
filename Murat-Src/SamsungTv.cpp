#include "../murat-devices/SamsungTV.h"
#include <iostream>

SamsungTV::SamsungTV() {
    currentChannel = 1;
}

void SamsungTV::turnOn() {
    std::cout << "[SamsungTV] Turning on." << std::endl;
}

void SamsungTV::turnOff() {
    std::cout << "[SamsungTV] Turning off." << std::endl;
}

void SamsungTV::setChannel(int ch) {
    currentChannel = ch;
    std::cout << "[SamsungTV] Channel set to: " << currentChannel << std::endl;
}
