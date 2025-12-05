#ifndef ALARMACTION_H
#define ALARMACTION_H

#include "AbstractActionHandler.h"
#include <string>

class AlarmAction : public AbstractActionHandler {
public:
    AlarmAction();
    ~AlarmAction();

    bool handle(const std::string& context);
};

#endif // ALARMACTION_H