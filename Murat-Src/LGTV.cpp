#include "../murat-devices/LGTV.h"
#include <iostream>

LGTV::LGTV() {
    currentChannel = 1;
}

void LGTV::turnOn() {
    std::cout << "[LGTV] Turning on." << std::endl;
}

void LGTV::turnOff() {
    std::cout << "[LGTV] Turning off." << std::endl;
}

void LGTV::setChannel(int ch) {
    currentChannel = ch;
    std::cout << "[LGTV] Channel set to: " << currentChannel << std::endl;
}
