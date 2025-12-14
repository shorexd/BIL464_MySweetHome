#include "Logic/SecuritySystem.h"
#include "Logic/AlarmAction.h"
#include "Logic/LightOnAction.h"
#include "Logic/CallPoliceAction.h"
#include <iostream>

SecuritySystem::SecuritySystem() {
    // Constructor (Bos kalabilir veya log atabilir)
}

SecuritySystem::~SecuritySystem() {
    // Destructor
}

void SecuritySystem::update(const std::string& eventType) {
    std::cout << "[SecuritySystem] Sinyal alindi: " << eventType << std::endl;

    if (eventType == "MOTION_DETECTED") {
        std::cout << "[SecuritySystem] !!! TEHLIKE !!! Hareket algilandi." << std::endl;
        executeSecurityChain();
    } else {
        std::cout << "[SecuritySystem] Bu sinyal guvenlik tehdidi degil." << std::endl;
    }
}

void SecuritySystem::executeSecurityChain() {
    std::cout << ">>> [ZINCIR KURULUYOR] Alarm -> Isik -> Polis <<<" << std::endl;

    // Zincir Halkalarini Olustur
    AbstractActionHandler* alarm = new AlarmAction();
    AbstractActionHandler* lights = new LightOnAction();
    AbstractActionHandler* police = new CallPoliceAction();

    // Zinciri Bagla: Alarm -> Isik -> Polis
    alarm->setNext(lights);
    lights->setNext(police);

    // FIX: Zinciri dogru "Context Key" ile baslatiyoruz.
    // LightOnAction ve CallPoliceAction "SECURITY_CHAIN" bekliyor.
    // Eskiden burasi "Guvenlik İhlali" oldugu icin sonraki adimlar calismiyordu.
    alarm->handle("SECURITY_CHAIN");

    // Temizlik (Zincir halkalarini siliyoruz)
    delete alarm;
    delete lights;
    delete police;

    std::cout << ">>> [ZINCIR TAMAMLANDI] Guvenlik protokolu sona erdi. <<<" << std::endl;
}