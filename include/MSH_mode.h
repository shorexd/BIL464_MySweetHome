#ifndef MSH_H
#define MSH_H

#include "Mode.h"
#include <string>

class MSH {
private:
    // LLR-M2: MSH, currentMode adinda bir Mode pointer saklamali
    Mode* currentMode;

public:
    MSH();
    ~MSH();

    // Mode Yonetimi
    void changeMode(Mode* newMode);
    std::string getModeName() const;
};

#endif