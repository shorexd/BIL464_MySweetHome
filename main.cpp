#include <iostream>
#include <limits>
#include "include/MSH.h"
#include "include/ConcreteStates.h"

// Durum bilgilerini gosteren panel fonksiyonu
void printDashboard(MSH* system) {
    std::cout << "\n+--------------------------------------+" << std::endl;
    std::cout << "|           SISTEM DURUM PANELI        |" << std::endl;
    std::cout << "+--------------------------------------+" << std::endl;
    std::cout << "| MOD        : " << system->getStateName() << std::endl;
    std::cout << "| PERFORMANS : " << system->getPerformance() << std::endl;
    std::cout << "| FAN HIZI   : " << system->getFanSpeed() << std::endl;
    std::cout << "| GUC TUKETIMI: " << system->getPowerUsage() << std::endl;
    std::cout << "+--------------------------------------+" << std::endl;
}

void printMenu() {
    std::cout << "1. Normal Mod | 2. Yuksek Perf. | 3. Guc Tasarrufu | 4. Uyku" << std::endl;
    std::cout << "5. Islem Yap  | 6. Kaydet       | 7. Geri Yukle    | 8. Cikis" << std::endl;
    std::cout << "Seciminiz: ";
}

int main() {
    MSH* system = new MSH();
    HomeStateMemento backup(NULL); 
    bool hasBackup = false; 

    int choice = 0;
    bool running = true;

    while (running) {
        // Yeni paneli burada cagiriyoruz
        printDashboard(system);
        printMenu();

        if (!(std::cin >> choice)) {
            std::cout << "Hatali giris!" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n'); 
            continue;
        }

        std::cout << std::endl;

        switch (choice) {
            case 1: system->changeState(new NormalState()); break;
            case 2: system->changeState(new HighPerformanceState()); break;
            case 3: system->changeState(new LowPowerState()); break;
            case 4: system->changeState(new SleepState()); break;
            case 5: system->requestAction(); break;
            case 6: 
                backup = system->saveState(); 
                hasBackup = true; 
                std::cout << ">> Durum ve tum veriler kaydedildi." << std::endl;
                break;
            case 7: 
                if(hasBackup) system->restoreState(backup); 
                else std::cout << ">> Kayit bulunamadi!" << std::endl;
                break;
            case 8: running = false; break;
            default: std::cout << "Gecersiz secim!" << std::endl; break;
        }
    }

    delete system;
    return 0;
}