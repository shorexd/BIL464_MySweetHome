#include "../include/ConcreteModes.h"
#include <iostream>

// LLR-M7: Kamera ve dedektorler her modda acik kalmali [cite: 94]
void printSafetyStatus() {
    std::cout << "   [GUVENLIK]: Kamera: ON | Smoke: ON | Gas: ON" << std::endl;
}

// --- Normal Mode ---
// LLR-M5: Light ON, TV OFF, Music OFF [cite: 89]
void NormalMode::apply(MSH* context) {
    std::cout << ">> [NormalMode] Configuration Applying..." << std::endl;
    std::cout << "   [CIHAZLAR]: Light: ON | TV: OFF | Music: OFF" << std::endl;
    printSafetyStatus();
}
std::string NormalMode::getName() const { return "Normal Mode"; }

// --- Evening Mode ---
// LLR-M5: Light OFF, TV OFF, Music OFF [cite: 89]
void EveningMode::apply(MSH* context) {
    std::cout << ">> [EveningMode] Configuration Applying..." << std::endl;
    std::cout << "   [CIHAZLAR]: Light: OFF | TV: OFF | Music: OFF" << std::endl;
    printSafetyStatus();
}
std::string EveningMode::getName() const { return "Evening Mode"; }

// --- Party Mode ---
// LLR-M5: Light ON, TV OFF, Music ON [cite: 89]
void PartyMode::apply(MSH* context) {
    std::cout << ">> [PartyMode] Configuration Applying..." << std::endl;
    std::cout << "   [CIHAZLAR]: Light: ON | TV: OFF | Music: ON" << std::endl;
    printSafetyStatus();
}
std::string PartyMode::getName() const { return "Party Mode"; }

// --- Cinema Mode ---
// LLR-M5: Light OFF, TV ON, Music OFF [cite: 89]
void CinemaMode::apply(MSH* context) {
    std::cout << ">> [CinemaMode] Configuration Applying..." << std::endl;
    std::cout << "   [CIHAZLAR]: Light: OFF | TV: ON | Music: OFF" << std::endl;
    printSafetyStatus();
}
std::string CinemaMode::getName() const { return "Cinema Mode"; }