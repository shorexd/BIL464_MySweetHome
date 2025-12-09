#include "../include/MSH_mode.h"
#include "../include/ConcreteModes.h"
#include <iostream>

MSH::MSH() {
    // LLR-M1: Baslangic modu NormalMode olmali [cite: 91]
    currentMode = new NormalMode();
    
    std::cout << "System Starting..." << std::endl;
    if(currentMode) {
        currentMode->apply(this);
    }
}

MSH::~MSH() {
    if (currentMode) {
        delete currentMode;
    }
}

// LLR-M6: Onceki moda ait cikis islemi yok, direkt degistir [cite: 26, 91]
void MSH::changeMode(Mode* newMode) {
    if (currentMode) {
        delete currentMode;
    }
    
    currentMode = newMode;

    if (currentMode) {
        // LLR-M8: Mode degisimi ekranda gosterilmeli [cite: 93]
        std::cout << "\n*** Mode changed to " << currentMode->getName() << " ***" << std::endl;
        
        // LLR-M9: apply fonksiyonu cagrilmali [cite: 42]
        currentMode->apply(this);
    }
}

std::string MSH::getModeName() const {
    return currentMode ? currentMode->getName() : "No Mode";
}