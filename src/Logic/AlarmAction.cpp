#include "Logic/AlarmAction.h"
#include <iostream>

AlarmAction::AlarmAction() {}

AlarmAction::~AlarmAction() {}

bool AlarmAction::handle(const std::string& context) {
    // Ortak Efekt: Hirsizda da Yanginda da bu calar
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "[AlarmAction] !!! ALARM CALIYOR !!! (Biiiiip Biiiiip)" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    // LLR-07: Eger Algilama Zinciri ise (Yangin/Gaz) -> KESILEBILIR
    if (context == "DETECTION_CHAIN") {
        std::cout << ">> [Sistem] Duman/Gaz tespit edildi!" << std::endl;
        std::cout << ">> [Sistem] Alarm 10 saniye boyunca caliyor..." << std::endl;
        std::cout << ">> [Sistem] Kullanici mudahelesi bekleniyor." << std::endl;
        std::cout << ">> Alarmi susturmak ve Itfaiyeyi iptal etmek ister misiniz? (e/h): ";
        
        char choice;
        std::cin >> choice;

        if (choice == 'e' || choice == 'E') {
            std::cout << ">> [AlarmAction] KULLANICI ONAYI: Alarm susturuldu. Itfaiye aranmayacak." << std::endl;
            // Zinciri kirmak icin true donuyoruz (sonraki halkaya gecmez)
            return true; 
        }
        
        std::cout << ">> [AlarmAction] Onay verilmedi veya sure doldu. Prosedur devam ediyor..." << std::endl;
    }

    // Guvenlik zinciri (Hirsiz) ise BURADAN DEVAM EDER (Kesintisiz)
    // Veya Yangin icin kullanici 'Hayir' dediyse devam eder.
    return AbstractActionHandler::handle(context);
}