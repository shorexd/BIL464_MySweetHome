#ifndef CALLFIRESTATIONACTION_H
#define CALLFIRESTATIONACTION_H

#include "AbstractActionHandler.h"
#include <string>

class CallFireStationAction : public AbstractActionHandler {
public:
    CallFireStationAction();
    ~CallFireStationAction();

    bool handle(const std::string& context);
};

#endif // CALLFIRESTATIONACTION_H