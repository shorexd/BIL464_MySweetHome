#include "AlarmAction.h"
#include <iostream>

AlarmAction::AlarmAction() {}

AlarmAction::~AlarmAction() {}

bool AlarmAction::handle(const std::string& context) {
    std::cout << "[AlarmAction] ALARM CALIYOR! (Biiiiip Biiiiip)" << std::endl;
    std::cout << "[AlarmAction] Senaryo: " << context << std::endl;

    // Burada normalde 10 saniye bekleme ve tuş kontrolü yapılır.
    // Şimdilik zincirin devam etmesi için doğrudan sonrakine paslıyoruz.
    
    return AbstractActionHandler::handle(context);
}