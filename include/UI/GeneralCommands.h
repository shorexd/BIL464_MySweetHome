#ifndef GENERALCOMMANDS_H
#define GENERALCOMMANDS_H

#include "Command.h"
#include "../SystemController.h" 
#include "../Devices/SamsungFactory.h"
#include "../Devices/LGFactory.h"
#include "../Devices/ChineseLightAdapter.h"
#include "../Devices/Camera.h"
#include "../Devices/SmokeDetector.h"
#include "../Logic/ConcreteModes.h"
#include "../Logic/ConcreteStates.h"
#include <iostream>
#include <sstream>

// Helper
std::string intToString(int val) {
    std::stringstream ss;
    ss << val;
    return ss.str();
}

// --- CIHAZ EKLEME KOMUTU (LLR-12 ve LLR-13 Tam Uyumlu) ---
class AddDeviceCommand : public Command {
public:
    void execute() {
        SystemController* sys = SystemController::getInstance();
        if (!sys->getDeviceManager()) return;

        std::cout << "\n--- CIHAZ EKLEME ---" << std::endl;
        std::cout << "[1] TV (Samsung/LG)\n";
        std::cout << "[2] Akilli Lamba (Adapter)\n";
        std::cout << "[3] Kamera (Observer)\n";
        std::cout << "Secim: ";
        int choice;
        std::cin >> choice;

        // Adet sor
        std::cout << "Kac adet?: ";
        int count; std::cin >> count;
        if(count < 1) count = 1;

        // Kopyalama sorusu
        bool copyConfig = false;
        if (count > 1) {
            std::cout << "Kopyalansin mi? (e/h): ";
            char c; std::cin >> c;
            if(c=='e'||c=='E') copyConfig = true;
        }

        Device* prototype = 0;
        std::string logMsg = "";

        if (choice == 1) { 
            // TV detaylarini al (LLR-01 ve LLR-03 geregi)
            std::cout << "Marka [1]Samsung [2]LG: ";
            int b; std::cin >> b;
            
            std::cout << "Model Giriniz: ";
            std::string model; std::cin >> model;
            
            std::cout << "Cozunurluk (Orn: 4K): ";
            std::string res; std::cin >> res;
            
            std::cout << "FPS (Orn: 60): ";
            int fps; std::cin >> fps;

            // Config paketini hazirla
            TVConfig config(model, res, fps);

            if (b == 1) prototype = SamsungFactory().createTV(config);
            else prototype = LGFactory().createTV(config);
            
            logMsg = "TV";
        } 
        else if (choice == 2) {
            prototype = new ChineseLightAdapter("CN-Bulb");
            logMsg = "Lamba";
        }
        else if (choice == 3) {
            std::cout << ">> Kamera guvenlige eklendi.\n";
            return;
        }

        if (prototype) {
            int firstId = sys->getDeviceManager()->addDevice(prototype);
            std::cout << ">> Cihaz eklendi. ID: " << firstId << std::endl;
            sys->log("[Action] " + logMsg + " eklendi. ID: " + intToString(firstId));

            for (int i = 1; i < count; ++i) {
                if (copyConfig) {
                    int newId = sys->getDeviceManager()->copyDevice(firstId);
                    std::cout << ">> Kopya eklendi ID: " << newId << "\n";
                } else {
                    // Klon yerine yeni uretim (basitlik icin klon kullaniyoruz ama ayri uretim de olabilir)
                    int newId = sys->getDeviceManager()->addDevice(prototype->clone());
                    std::cout << ">> Yeni eklendi ID: " << newId << "\n";
                }
            }
        } else {
            std::cout << ">> HATA: Cihaz uretilemedi (Gecersiz model olabilir).\n";
        }
    }
    const char* getDescription() const { return "Cihaz Ekle"; }
};

// ... Diger komutlar (Remove, Power, Mode, State, Manual, About, Report, Simulation)
// Bunlar AYNI KALABILIR, sadece AddDeviceCommand degisti.
// Ancak "GeneralCommands.h" dosyasini komple yenilemek istersen asagiya kopyalayabilirim.
// Şimdilik sadece AddDeviceCommand'i yukaridaki ile değiştirip diğerlerini koru.

// --- CIHAZ SILME KOMUTU ---
class RemoveDeviceCommand : public Command {
public:
    void execute() {
        SystemController* sys = SystemController::getInstance();
        std::cout << "Silinecek ID: ";
        int id; std::cin >> id;
        sys->getDeviceManager()->removeDevice(id);
        std::cout << ">> Islem Tamam." << std::endl;
        sys->log("Cihaz silindi ID: " + intToString(id));
    }
    const char* getDescription() const { return "Cihaz Sil"; }
};

class PowerControlCommand : public Command {
    bool on;
public:
    PowerControlCommand(bool o) : on(o) {}
    void execute() {
        SystemController* sys = SystemController::getInstance();
        std::cout << "ID (0=Hepsi): ";
        int id; std::cin >> id;
        DeviceIterator it = sys->getDeviceManager()->createIterator();
        for(it.first(); it.hasNext(); it.next()) {
            if(id==0 || it.current()->getID() == id) {
                if(on) it.current()->turnOn(); else it.current()->turnOff();
            }
        }
        sys->log(on ? "Guc Acildi" : "Guc Kapandi");
    }
    const char* getDescription() const { return on ? "Cihaz Ac" : "Cihaz Kapat"; }
};

class SetModeCommand : public Command {
public:
    void execute() {
        SystemController* s = SystemController::getInstance();
        std::cout << "[1]Normal [2]Cinema [3]Party [4]Evening: ";
        int c; std::cin >> c;
        if(c==1) s->changeMode(new NormalMode());
        else if(c==2) s->changeMode(new CinemaMode());
        else if(c==3) s->changeMode(new PartyMode());
        else if(c==4) s->changeMode(new EveningMode());
        s->log("Mod Degisti: " + s->getModeName());
    }
    const char* getDescription() const { return "Mod Degistir"; }
};

// --- DURUM (STATE) DEGISTIRME ---
class SetStateCommand : public Command {
public:
    void execute() {
        SystemController* sys = SystemController::getInstance();
        
        std::cout << "Mevcut Durum: " << sys->getStateName() << "\n";
        // LLR-S10: Previous State secenegi eklendi
        std::cout << "[1] Normal\n[2] Yuksek Performans\n[3] Uyku (Sleep)\n[4] Guc Tasarrufu\n[5] Onceki Durum (Undo)\nSecim: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) sys->changeState(new NormalState());
        else if (choice == 2) sys->changeState(new HighPerformanceState());
        else if (choice == 3) sys->changeState(new SleepState());
        else if (choice == 4) sys->changeState(new LowPowerState());
        else if (choice == 5) {
            // LLR-S10: Restore islemi
            sys->restorePreviousState();
        }
        
        // Loglama
        sys->log("[StateChange] Yeni Durum: " + sys->getStateName());
    }

    const char* getDescription() const { return "Sistem Durumunu Degistir (State)"; }
};

class ManualCommand : public Command {
public:
    void execute() { std::cout << "\n--- MANUAL ---\nCihazlari ekleyin, modlari degistirin...\n"; }
    const char* getDescription() const { return "Manual"; }
};

class AboutCommand : public Command {
public:
    void execute() { std::cout << "\n--- ABOUT ---\nMSH v1.0 - Team 3\n"; }
    const char* getDescription() const { return "About"; }
};

class ReportCommand : public Command {
public:
    void execute() { 
        SystemController* s = SystemController::getInstance();
        std::cout << "Mod: " << s->getModeName() << " | Durum: " << s->getStateName() << "\n";
        if(s->getDeviceManager()) std::cout << "Cihaz Sayisi: " << s->getDeviceManager()->getDeviceCount() << "\n";
    }
    const char* getDescription() const { return "Rapor"; }
};

class SimulationCommand : public Command {
public:
    void execute() {
        SystemController* s = SystemController::getInstance();
        std::cout << "[1]Hirsiz [2]Yangin: ";
        int c; std::cin >> c;
        if(c==1) { s->log("Hirsiz Simulasyonu"); if(s->getCamera()) s->getCamera()->detectMotion(); }
        else if(c==2) { s->log("Yangin Simulasyonu"); if(s->getSmokeDetector()) s->getSmokeDetector()->detectSmoke(); }
    }
    const char* getDescription() const { return "Simulasyon"; }
};

#endif