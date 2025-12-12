#include "Logic/ConcreteModes.h"
#include "SystemController.h"
#include "Devices/DeviceManager.h"
#include "Devices/DeviceIterator.h" // Yunus'un Iterator'i
#include "Devices/Device.h"
#include <iostream>

// --- YARDIMCI FONKSIYON ---
// Bu fonksiyon cihaz listesini gezer ve isimlere gore acip kapatir.
void applyToDevices(SystemController* context, bool lightsOn, bool tvOn, bool musicOn) {
    if (!context->getDeviceManager()) return;

    // Yunus'un Iterator deseni ile cihazlari geziyoruz
    DeviceIterator it = context->getDeviceManager()->createIterator();
    for (it.first(); it.hasNext(); it.next()) {
        Device* d = it.current();
        if (!d) continue;

        std::string name = d->getName(); 
        
        // Basit string kontrolu ile cihaz turunu anliyoruz:
        
        // 1. ISIKLAR
        if (name.find("Light") != std::string::npos || name.find("Lamba") != std::string::npos) {
            if (lightsOn) d->turnOn(); else d->turnOff();
        }
        // 2. TV'LER
        else if (name.find("TV") != std::string::npos) {
            if (tvOn) d->turnOn(); else d->turnOff();
        }
        // 3. MUZIK (Varsa)
        else if (name.find("Music") != std::string::npos) {
            if (musicOn) d->turnOn(); else d->turnOff();
        }
        
        // LLR-M7: Kamera ve Dedektorler'e DOKUNMUYORUZ (Hep acik kalmalilar).
    }
}

// --- Normal Mode ---
// LLR-M5: Light ON, TV OFF, Music OFF
void NormalMode::apply(SystemController* context) {
    std::cout << ">> [Mode] Normal Mod Aktif Ediliyor..." << std::endl;
    applyToDevices(context, true, false, false); 
}
std::string NormalMode::getName() const { return "Normal Mode"; }

// --- Evening Mode ---
// LLR-M5: Light OFF, TV OFF, Music OFF
void EveningMode::apply(SystemController* context) {
    std::cout << ">> [Mode] Aksam Modu (Evening) Aktif Ediliyor..." << std::endl;
    applyToDevices(context, false, false, false);
}
std::string EveningMode::getName() const { return "Evening Mode"; }

// --- Party Mode ---
// LLR-M5: Light ON, TV OFF, Music ON
void PartyMode::apply(SystemController* context) {
    std::cout << ">> [Mode] Parti Modu! Isiklar ve Muzik aciliyor..." << std::endl;
    applyToDevices(context, true, false, true);
}
std::string PartyMode::getName() const { return "Party Mode"; }

// --- Cinema Mode ---
// LLR-M5: Light OFF, TV ON, Music OFF
void CinemaMode::apply(SystemController* context) {
    std::cout << ">> [Mode] Sinema Modu. Isiklar kapaniyor, TV aciliyor..." << std::endl;
    applyToDevices(context, false, true, false);
}
std::string CinemaMode::getName() const { return "Cinema Mode"; }