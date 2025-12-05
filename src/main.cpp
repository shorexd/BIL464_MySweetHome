/* 
 * File: src/main.cpp
 * Project: My Sweet Home
 * Standard: C++98
 */

#include <iostream>
#include <string>
#include "Logger.h"
#include "Devices/ChineseLightAdapter.h"

// Ileride buraya diger header'lar eklenecek
// #include "Devices/Device.h"

void displayMenu() {
    std::cout << "\n=== MY SWEET HOME (MSH) ===" << std::endl;
    std::cout << "[1] Get Home Status" << std::endl;
    std::cout << "[2] Add Device" << std::endl;
    std::cout << "[3] Remove Device" << std::endl;
    std::cout << "[4] Power on Device" << std::endl;
    std::cout << "[5] Power off Device" << std::endl;
    std::cout << "[6] Change Mode" << std::endl;
    std::cout << "[7] Change State" << std::endl;
    std::cout << "[8] Manual" << std::endl;
    std::cout << "[9] About" << std::endl;
    std::cout << "[10] Shutdown" << std::endl;
    std::cout << "Select option: ";
}

int main() {
    // --- Ali: Logger ve ChineseLightAdapter baslangic ayarlari ---
    std::cout << "[System] Log file created." << std::endl;
    std::cout << "[System] Initializing in NORMAL Mode..." << std::endl;

    // Log dosyasini ac
    Logger::getInstance().open();
    Logger::getInstance().log("System started in NORMAL Mode");

    // Tek bir Cin mali isik cihazini adapter ile temsil ediyoruz
    ChineseLightAdapter livingRoomLight("CN-LivingRoom-01");
    Logger::getInstance().log("ChineseLightAdapter created for CN-LivingRoom-01");
    // ---------------------------------------------------------------

    bool running = true;
    int choice;

    while (running) {
        displayMenu();

        if (!(std::cin >> choice)) {
            // Hatali giris kontrolu
            std::cin.clear();
            std::string ignoreLine;
            std::getline(std::cin, ignoreLine);
            std::cout << "Invalid input! Please enter a number." << std::endl;

            Logger::getInstance().log("Invalid menu input (non-numeric)");
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << ">> Showing Status (Mockup)..." << std::endl;
                Logger::getInstance().log("Menu: Get Home Status selected");
                break;

            case 2:
                std::cout << ">> Add Device selected." << std::endl;
                Logger::getInstance().log("Menu: Add Device selected (not implemented)");
                break;

            case 3:
                std::cout << ">> Remove Device selected." << std::endl;
                Logger::getInstance().log("Menu: Remove Device selected (not implemented)");
                break;

            case 4:
                std::cout << ">> Power on Device selected." << std::endl;
                Logger::getInstance().log("Menu: Power on Device selected");

                // Cin mali isik cihazini ac ve parlakligini ayarla
                livingRoomLight.turnOn();
                livingRoomLight.setBrightnessPercent(70); // Ornek: %70 parlaklik

                std::cout << ">> Chinese light powered ON at "
                          << livingRoomLight.currentPercent() << "% brightness."
                          << std::endl;
                break;

            case 5:
                std::cout << ">> Power off Device selected." << std::endl;
                Logger::getInstance().log("Menu: Power off Device selected");

                livingRoomLight.turnOff();
                std::cout << ">> Chinese light powered OFF." << std::endl;
                break;

            case 6:
                std::cout << ">> Change Mode selected (Not implemented yet)." << std::endl;
                Logger::getInstance().log("Menu: Change Mode selected (not implemented)");
                break;

            case 7:
                std::cout << ">> Change State selected (Not implemented yet)." << std::endl;
                Logger::getInstance().log("Menu: Change State selected (not implemented)");
                break;

            case 8:
                std::cout << ">> Manual selected (Not implemented yet)." << std::endl;
                Logger::getInstance().log("Menu: Manual selected (not implemented)");
                break;

            case 9:
                std::cout << ">> About selected (Not implemented yet)." << std::endl;
                Logger::getInstance().log("Menu: About selected (not implemented)");
                break;

            case 10:
                std::cout << "Shutting down system..." << std::endl;
                std::cout << "[System] Log file closed." << std::endl;

                Logger::getInstance().log("Menu: Shutdown selected");
                running = false;
                break;

            default:
                std::cout << ">> Option " << choice 
                          << " selected (Not implemented yet)." << std::endl;
                Logger::getInstance().log("Menu: Unknown option selected");
                break;
        }
    }

    // --- Ali: Logger'i duzgun kapat ---
    Logger::getInstance().log("System shutting down");
    Logger::getInstance().close();

    return 0;
}
