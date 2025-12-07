#include "../include/ConcreteStates.h"
#include "../include/MSH.h"
#include <iostream>

// --- NORMAL STATE ---
void NormalState::enterState(MSH* context) { std::cout << "[NormalState] Giris yapildi.\n"; }
void NormalState::exitState(MSH* context) { std::cout << "[NormalState] Cikis yapiliyor.\n"; }
void NormalState::handle(MSH* context) { std::cout << "Islem: Standart kullanim modu aktif.\n"; }
std::string NormalState::getName() const { return "Normal Mod"; }
HomeState* NormalState::clone() const { return new NormalState(*this); }

// Normal State Degerleri
std::string NormalState::getPerformance() const { return "Dengeli"; }
std::string NormalState::getFanSpeed() const { return "1500 RPM (Sessiz)"; }
std::string NormalState::getPowerUsage() const { return "%40"; }


// --- HIGH PERFORMANCE STATE ---
void HighPerformanceState::enterState(MSH* context) { std::cout << "[HighPerformance] Giris yapildi. Fanlar tam gaz!\n"; }
void HighPerformanceState::exitState(MSH* context) { std::cout << "[HighPerformance] Cikis yapiliyor.\n"; }
void HighPerformanceState::handle(MSH* context) { std::cout << "Islem: Render ve oyun icin maksimum guc!\n"; }
std::string HighPerformanceState::getName() const { return "Yuksek Performans"; }
HomeState* HighPerformanceState::clone() const { return new HighPerformanceState(*this); }

// High Perf Degerleri
std::string HighPerformanceState::getPerformance() const { return "Ultra Yuksek"; }
std::string HighPerformanceState::getFanSpeed() const { return "5000 RPM (Turbo)"; }
std::string HighPerformanceState::getPowerUsage() const { return "%95"; }


// --- LOW POWER STATE ---
void LowPowerState::enterState(MSH* context) { std::cout << "[LowPower] Giris yapildi. Isiklar kisildi.\n"; }
void LowPowerState::exitState(MSH* context) { std::cout << "[LowPower] Cikis yapiliyor.\n"; }
void LowPowerState::handle(MSH* context) { std::cout << "Islem: Arkaplan uygulamalari durduruldu.\n"; }
std::string LowPowerState::getName() const { return "Guc Tasarrufu"; }
HomeState* LowPowerState::clone() const { return new LowPowerState(*this); }

// Low Power Degerleri
std::string LowPowerState::getPerformance() const { return "Kisitlanmis"; }
std::string LowPowerState::getFanSpeed() const { return "0 RPM (Pasif)"; }
std::string LowPowerState::getPowerUsage() const { return "%15"; }


// --- SLEEP STATE ---
void SleepState::enterState(MSH* context) { std::cout << "[Sleep] Uyku modu.\n"; }
void SleepState::exitState(MSH* context) { std::cout << "[Sleep] Uyaniliyor...\n"; }
void SleepState::handle(MSH* context) { std::cout << "Islem: Sistem yanit vermiyor (Uykuda).\n"; }
std::string SleepState::getName() const { return "Uyku Modu"; }
HomeState* SleepState::clone() const { return new SleepState(*this); }

// Sleep Degerleri
std::string SleepState::getPerformance() const { return "Durduruldu"; }
std::string SleepState::getFanSpeed() const { return "Kapali"; }
std::string SleepState::getPowerUsage() const { return "%1"; }