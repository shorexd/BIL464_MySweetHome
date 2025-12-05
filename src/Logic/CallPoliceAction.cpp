#include "CallPoliceAction.h"
#include <iostream>

CallPoliceAction::CallPoliceAction() {}

CallPoliceAction::~CallPoliceAction() {}

bool CallPoliceAction::handle(const std::string& context) {
    if (context == "SECURITY_CHAIN") {
        std::cout << "[CallPoliceAction] POLIS ARANIYOR... (155)" << std::endl;
        // Zincirin sonu, true döndürüp bitiriyoruz.
        return true; 
    }
    return AbstractActionHandler::handle(context);
}