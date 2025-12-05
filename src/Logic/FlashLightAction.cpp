#include "FlashLightAction.h"
#include <iostream>

FlashLightAction::FlashLightAction() {}

FlashLightAction::~FlashLightAction() {}

bool FlashLightAction::handle(const std::string& context) {
    // Bu eylem SADECE Algılama (Detection) zincirinde çalışmalı
    if (context == "DETECTION_CHAIN") {
        std::cout << "[FlashLightAction] Isiklar YANIP SONUYOR (Flasher modu)!" << std::endl;
        return AbstractActionHandler::handle(context);
    }
    
    // Eğer algılama değilse pas geç
    return AbstractActionHandler::handle(context);
}