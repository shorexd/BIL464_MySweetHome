#include <iostream>
#include <limits>
#include "include/MSH_mode.h"
#include "include/ConcreteModes.h"
#include <chrono>
#include <thread>

void printDashboard(MSH* system) {
    std::cout << "\n+-----------------------------------+" << std::endl;
    std::cout << "| ACTIVE MODE: " << system->getModeName() << std::endl;
    std::cout << "+-----------------------------------+" << std::endl;
}

void printMenu() {
    // Dökümandaki Mode secenekleri [cite: 56]
    std::cout << "1. Normal Mode" << std::endl;
    std::cout << "2. Evening Mode" << std::endl;
    std::cout << "3. Party Mode" << std::endl;
    std::cout << "4. Cinema Mode" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Select: ";
}

int main() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    MSH* system = new MSH();
    int choice = 0;
    bool running = true;

    while (running) {
        sleep_for(seconds(1));
        sleep_until(system_clock::now() + seconds(1));
        printDashboard(system);
        printMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        std::cout << std::endl;

        switch (choice) {
            case 1: system->changeMode(new NormalMode()); break;
            case 2: system->changeMode(new EveningMode()); break;
            case 3: system->changeMode(new PartyMode()); break;
            case 4: system->changeMode(new CinemaMode()); break;
            case 5: running = false; break;
            default: std::cout << "Invalid choice!" << std::endl; break;
        }
    }

    delete system;
    return 0;
}