#ifndef CALLPOLICEACTION_H
#define CALLPOLICEACTION_H

#include "AbstractActionHandler.h"
#include <string>

class CallPoliceAction : public AbstractActionHandler {
public:
    CallPoliceAction();
    ~CallPoliceAction();

    bool handle(const std::string& context) override;
};

#endif // CALLPOLICEACTION_H