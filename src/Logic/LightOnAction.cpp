#include "LightOnAction.h"
#include <iostream>

LightOnAction::LightOnAction() {}

LightOnAction::~LightOnAction() {}

bool LightOnAction::handle(const std::string& context) {
    // Bu eylem SADECE Güvenlik (Security) zincirinde çalışmalı
    if (context == "SECURITY_CHAIN") {
        std::cout << "[LightOnAction] Isiklar ACILDI (Surekli yaniyor)." << std::endl;
        return AbstractActionHandler::handle(context);
    }
    
    // Eğer güvenlik değilse, zinciri kırmadan pas geçiyoruz
    return AbstractActionHandler::handle(context);
}