#include "CallFireStationAction.h"
#include <iostream>

CallFireStationAction::CallFireStationAction() {}

CallFireStationAction::~CallFireStationAction() {}

bool CallFireStationAction::handle(const std::string& context) {
    if (context == "DETECTION_CHAIN") {
        std::cout << "[CallFireStationAction] ITFAIYE ARANIYOR... (110)" << std::endl;
        return true;
    }
    return AbstractActionHandler::handle(context);
}