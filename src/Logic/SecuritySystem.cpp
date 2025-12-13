#include "Logic/SecuritySystem.h"
#include "Logic/AlarmAction.h"
#include "Logic/LightOnAction.h"
#include "Logic/CallPoliceAction.h"
#include <iostream> // <--- EKSIK OLAN BUYDU, EKLENDI

SecuritySystem::SecuritySystem() {
    std::cout << "[SecuritySystem] Guvenlik sistemi aktif edildi." << std::endl;
}

SecuritySystem::~SecuritySystem() {
    std::cout << "[SecuritySystem] Guvenlik sistemi kapatiliyor." << std::endl;
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
    // (Not: Gercek uygulamada bunlari member olarak tutmak daha iyidir ama 
    // odevi karmasiklastirmamak icin burada yerel uretiyoruz)
    AlarmAction* alarm = new AlarmAction();
    LightOnAction* lights = new LightOnAction();
    CallPoliceAction* police = new CallPoliceAction();

    // Zinciri Bagla: Alarm -> Isik -> Polis
    alarm->setNext(lights);
    lights->setNext(police);

    // Zinciri Baslat
    alarm->handle("Guvenlik İhlali");

    // Temizlik (Zincir halkalarini siliyoruz)
    delete alarm;
    delete lights;
    delete police;

    std::cout << ">>> [ZINCIR TAMAMLANDI] Guvenlik protokolu sona erdi. <<<" << std::endl;
}