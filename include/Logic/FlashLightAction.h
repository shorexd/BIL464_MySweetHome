#ifndef FLASHLIGHTACTION_H
#define FLASHLIGHTACTION_H

#include "AbstractActionHandler.h"
#include <string>

class FlashLightAction : public AbstractActionHandler {
public:
    FlashLightAction();
    ~FlashLightAction();

    bool handle(const std::string& context);
};

#endif // FLASHLIGHTACTION_H