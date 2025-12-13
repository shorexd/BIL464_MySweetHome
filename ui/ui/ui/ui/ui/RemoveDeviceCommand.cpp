#include "RemoveDeviceCommand.h"
#include <iostream>
#include <vector>
#include "../include/SystemController.h"
#include "../include/Devices/Device.h"

void RemoveDeviceCommand::execute() {
    const std::vector<Device*>& devices =
        SystemController::getInstance()
            .getDeviceManager()
            .getDevices();

    if (devices.empty()) {
        std::cout << "No devices found.\n";
        return;
    }

    std::cout << "Existing devices:\n";
    for (size_t i = 0; i < devices.size(); ++i) {
        std::cout << "ID: " << devices[i]->getId()
                  << " Type: " << devices[i]->getType()
                  << std::endl;
    }

    int id;
    std::cout << "Enter device ID to remove: ";
    std::cin >> id;

    SystemController::getInstance()
        .getDeviceManager()
        .removeDevice(id);

    SystemController::getInstance().log("RemoveDeviceCommand executed");
}
