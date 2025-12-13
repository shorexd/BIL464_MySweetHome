#include "Logic/ConcreteStates.h"
#include "SystemController.h" 
#include <iostream>

// --- NORMAL STATE ---
void NormalState::enterState(SystemController* /*context*/) { 
    std::cout << "[NormalState] Giris yapildi.\n"; 
}
void NormalState::exitState(SystemController* /*context*/) { 
    std::cout << "[NormalState] Cikis yapiliyor.\n"; 
}
void NormalState::handle(SystemController* /*context*/) { 
    std::cout << "Islem: Standart kullanim modu aktif.\n"; 
}
std::string NormalState::getName() const { return "Normal Mod"; }
HomeState* NormalState::clone() const { return new NormalState(*this); }
std::string NormalState::getPerformance() const { return "Dengeli"; }
std::string NormalState::getFanSpeed() const { return "1500 RPM"; }
std::string NormalState::getPowerUsage() const { return "%40"; }

// --- HIGH PERFORMANCE STATE ---
void HighPerformanceState::enterState(SystemController* /*context*/) { 
    std::cout << "[HighPerformance] Giris: Fanlar tam gaz!\n"; 
}
void HighPerformanceState::exitState(SystemController* /*context*/) { 
    std::cout << "[HighPerformance] Cikis.\n"; 
}
void HighPerformanceState::handle(SystemController* /*context*/) { 
    std::cout << "Islem: Maksimum guc!\n"; 
}
std::string HighPerformanceState::getName() const { return "Yuksek Performans"; }
HomeState* HighPerformanceState::clone() const { return new HighPerformanceState(*this); }
std::string HighPerformanceState::getPerformance() const { return "Ultra Yuksek"; }
std::string HighPerformanceState::getFanSpeed() const { return "5000 RPM"; }
std::string HighPerformanceState::getPowerUsage() const { return "%95"; }

// --- LOW POWER STATE ---
void LowPowerState::enterState(SystemController* /*context*/) { 
    std::cout << "[LowPower] Giris: Isiklar kisildi.\n"; 
}
void LowPowerState::exitState(SystemController* /*context*/) { 
    std::cout << "[LowPower] Cikis.\n"; 
}
void LowPowerState::handle(SystemController* /*context*/) { 
    std::cout << "Islem: Tasarruf modu.\n"; 
}
std::string LowPowerState::getName() const { return "Guc Tasarrufu"; }
HomeState* LowPowerState::clone() const { return new LowPowerState(*this); }
std::string LowPowerState::getPerformance() const { return "Kisitlanmis"; }
std::string LowPowerState::getFanSpeed() const { return "0 RPM"; }
std::string LowPowerState::getPowerUsage() const { return "%15"; }

// --- SLEEP STATE ---
void SleepState::enterState(SystemController* /*context*/) { 
    std::cout << "[Sleep] Uyku modu.\n"; 
}
void SleepState::exitState(SystemController* /*context*/) { 
    std::cout << "[Sleep] Uyaniliyor...\n"; 
}
void SleepState::handle(SystemController* /*context*/) { 
    std::cout << "Islem: Sistem uykuda.\n"; 
}
std::string SleepState::getName() const { return "Uyku Modu"; }
HomeState* SleepState::clone() const { return new SleepState(*this); }
std::string SleepState::getPerformance() const { return "Durduruldu"; }
std::string SleepState::getFanSpeed() const { return "Kapali"; }
std::string SleepState::getPowerUsage() const { return "%1"; }