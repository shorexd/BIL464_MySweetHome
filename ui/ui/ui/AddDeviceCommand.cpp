#include "AddDeviceCommand.h"
#include <iostream>
#include "../include/SystemController.h"

void AddDeviceCommand::execute() {
    char type;
    int count;

    std::cout << "Device type (L:Light, C:Camera, D:Door, T:Thermostat): ";
    std::cin >> type;

    std::cout << "How many devices: ";
    std::cin >> count;

    bool copyConfig = false;
    if (count > 1) {
        char c;
        std::cout << "Copy config? (y/n): ";
        std::cin >> c;
        copyConfig = (c == 'y' || c == 'Y');
    }

    for (int i = 0; i < count; ++i) {
        SystemController::getInstance()
            .getDeviceManager()
            .addDevice(type, copyConfig);
    }

    SystemController::getInstance().log("AddDeviceCommand executed");
}
