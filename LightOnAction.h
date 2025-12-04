#ifndef LIGHTONACTION_H
#define LIGHTONACTION_H

#include "AbstractActionHandler.h"
#include <string>

class LightOnAction : public AbstractActionHandler {
public:
    LightOnAction();
    ~LightOnAction();

    bool handle(const std::string& context) override;
};

#endif // LIGHTONACTION_H