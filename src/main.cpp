/* * File: src/main.cpp
 * Project: My Sweet Home
 * Standard: C++98
 */

#include <iostream>
#include <string>

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
    std::cout << "[System] Log file created." << std::endl;
    std::cout << "[System] Initializing in NORMAL Mode..." << std::endl;

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
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << ">> Showing Status (Mockup)..." << std::endl;
                break;
            case 2:
                std::cout << ">> Add Device selected." << std::endl;
                break;
            case 10:
                std::cout << "Shutting down system..." << std::endl;
                std::cout << "[System] Log file closed." << std::endl;
                running = false;
                break;
            default:
                std::cout << ">> Option " << choice << " selected (Not implemented yet)." << std::endl;
                break;
        }
    }

    return 0;
}