#include "AbstractActionHandler.h"

AbstractActionHandler::AbstractActionHandler() : next_handler(nullptr) {}

AbstractActionHandler::~AbstractActionHandler() {}

AbstractActionHandler* AbstractActionHandler::setNext(AbstractActionHandler* handler) {
    this->next_handler = handler;
    return handler;
}

bool AbstractActionHandler::handle(const std::string& context) {
    if (this->next_handler) {
        return this->next_handler->handle(context);
    }
    return true;
}