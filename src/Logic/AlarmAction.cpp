#include "Logic/AlarmAction.h"
#include <iostream>

AlarmAction::AlarmAction() {}

AlarmAction::~AlarmAction() {}

bool AlarmAction::handle(const std::string& context) {
    std::cout << "[AlarmAction] ALARM CALIYOR! (Biiiiip Biiiiip)" << std::endl;

    // LLR-07: Eger Algilama Zinciri ise (Yangin/Gaz)
    if (context == "DETECTION_CHAIN") {
        std::cout << ">> [Sistem] Alarm 10 saniye boyunca caliyor..." << std::endl;
        std::cout << ">> [Sistem] Kullanici mudahelesi bekleniyor (Simulasyon)." << std::endl;
        std::cout << ">> Alarmi susturmak istiyor musunuz? (e/h): ";
        
        char choice;
        std::cin >> choice;

        if (choice == 'e' || choice == 'E') {
            std::cout << ">> [AlarmAction] Kullanici alarmi kapatti. Zincir durduruluyor." << std::endl;
            // Zinciri kirmak icin next_handler'i cagirmiyoruz, true donuyoruz.
            return true; 
        }
        
        std::cout << ">> [AlarmAction] Sure doldu, mudahale yok. Diger onlemlere geciliyor..." << std::endl;
    }

    // Guvenlik zinciri ise veya kullanici susturmadiysa siradaki halkaya gec
    return AbstractActionHandler::handle(context);
}