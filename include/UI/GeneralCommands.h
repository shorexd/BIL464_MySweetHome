#ifndef GENERALCOMMANDS_H
#define GENERALCOMMANDS_H

#include "Command.h"
#include "../SystemController.h" 
#include "../Devices/SamsungFactory.h"
#include "../Devices/LGFactory.h"
#include "../Devices/ChineseLightAdapter.h" // Adapter Pattern
#include "../Devices/Camera.h"
#include "../Devices/SmokeDetector.h"
#include "../Logic/ConcreteModes.h"
#include "../Logic/ConcreteStates.h"
#include <iostream>
#include <sstream> // String stream icin

// --- YARDIMCI: Int to String (C++98 uyumlu) ---
std::string intToString(int val) {
    std::stringstream ss;
    ss << val;
    return ss.str();
}

// --- CIHAZ EKLEME KOMUTU (Gelistirilmis) ---
class AddDeviceCommand : public Command {
public:
    void execute() {
        SystemController* sys = SystemController::getInstance();
        if (!sys->getDeviceManager()) return;

        std::cout << "\n--- CIHAZ EKLEME SIHIRBAZI ---" << std::endl;
        std::cout << "[1] TV (Samsung/LG - Abstract Factory)\n";
        std::cout << "[2] Akilli Lamba (Cin Mali - Adapter Pattern)\n";
        std::cout << "[3] Kamera (Observer Subject)\n";
        std::cout << "Secim: ";
        int choice;
        std::cin >> choice;

        Device* newDevice = 0;
        std::string logMsg = "";

        if (choice == 1) { // TV
            std::cout << "Marka: [1] Samsung, [2] LG: ";
            int brand;
            std::cin >> brand;
            if (brand == 1) { SamsungFactory sf; newDevice = sf.createTV(); }
            else if (brand == 2) { LGFactory lf; newDevice = lf.createTV(); }
            logMsg = "TV Eklendi";
        } 
        else if (choice == 2) { // LAMBA
            // FIX 1: Adapter parametre istiyordu, string verdik.
            newDevice = new ChineseLightAdapter("CN-SmartBulb-V1");
            logMsg = "Akilli Lamba (Adapter) Eklendi";
        }
        else if (choice == 3) { // KAMERA
            // FIX 2: Camera, Device sinifindan turetmemis olabilir. 
            // DeviceManager'a eklemeye zorlayip hata almak yerine
            // sadece sisteme bilgi veriyoruz.
            std::cout << ">> Kamera Guvenlik Sistemine Baglandi (Sensor)." << std::endl;
            sys->log("[UserAction] Kamera guvenlik sistemine eklendi.");
            return; // DeviceManager'a eklemeden cikiyoruz
        }

        if (newDevice) {
            int id = sys->getDeviceManager()->addDevice(newDevice);
            std::cout << ">> BASARILI: Cihaz eklendi. ID: " << id << std::endl;
            sys->log("[UserAction] " + logMsg + " ID: " + intToString(id));
        } else {
            std::cout << ">> HATA: Gecersiz secim veya Cihaz olusturulamadi." << std::endl;
        }
    }

    const char* getDescription() const { return "Cihaz Ekle (TV, Lamba, Kamera)"; }
};

// --- CIHAZ SILME KOMUTU ---
class RemoveDeviceCommand : public Command {
public:
    void execute() {
        SystemController* sys = SystemController::getInstance();
        if (!sys->getDeviceManager()) return;

        std::cout << "Silinecek Cihaz ID: ";
        int id;
        std::cin >> id;

        sys->getDeviceManager()->removeDevice(id);
        std::cout << ">> Islem tamamlandi." << std::endl;
        sys->log("[UserAction] Cihaz silme istegi gonderildi. ID: " + intToString(id));
    }

    const char* getDescription() const { return "Cihaz Sil"; }
};

// --- GUC YONETIMI (Power On/Off) - REQ 6 ---
class PowerControlCommand : public Command {
private:
    bool turnOn; // true: ac, false: kapat
public:
    PowerControlCommand(bool on) : turnOn(on) {}
    
    void execute() {
        SystemController* sys = SystemController::getInstance();
        if (!sys->getDeviceManager()) return;

        std::cout << "Islem yapilacak Cihaz ID (0 = Hepsi): ";
        int id;
        std::cin >> id;

        DeviceIterator it = sys->getDeviceManager()->createIterator();
        for (it.first(); it.hasNext(); it.next()) {
            Device* d = it.current();
            // FIX 3: getId() degil getID() olmali (Buyuk harf duyarliligi)
            if (d && (id == 0 || d->getID() == id)) {
                if (turnOn) d->turnOn();
                else d->turnOff();
            }
        }
        std::string action = turnOn ? "ACILDI" : "KAPATILDI";
        sys->log("[UserAction] Cihaz guc durumu degistirildi: " + action);
        std::cout << ">> Komut gonderildi." << std::endl;
    }

    const char* getDescription() const { 
        return turnOn ? "Cihaz Ac (Power On)" : "Cihaz Kapat (Power Off)"; 
    }
};

// --- MOD DEGISTIRME ---
class SetModeCommand : public Command {
public:
    void execute() {
        SystemController* sys = SystemController::getInstance();
        
        std::cout << "Mevcut Mod: " << sys->getModeName() << "\n";
        std::cout << "[1] Normal\n[2] Sinema (TV On, Light Off)\n[3] Parti (Light On)\n[4] Aksam\nSecim: ";
        int choice;
        std::cin >> choice;

        Mode* m = 0;
        if (choice == 1) m = new NormalMode();
        else if (choice == 2) m = new CinemaMode();
        else if (choice == 3) m = new PartyMode();
        else if (choice == 4) m = new EveningMode();

        if (m) {
            sys->changeMode(m);
            sys->log("[ModeChange] Yeni Mod: " + sys->getModeName());
        }
    }

    const char* getDescription() const { return "Mod Degistir (Scene Management)"; }
};

// --- DURUM (STATE) DEGISTIRME ---
class SetStateCommand : public Command {
public:
    void execute() {
        SystemController* sys = SystemController::getInstance();
        
        std::cout << "Mevcut Durum: " << sys->getStateName() << "\n";
        std::cout << "[1] Normal\n[2] Yuksek Performans\n[3] Uyku (Sleep)\n[4] Guc Tasarrufu\nSecim: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) sys->changeState(new NormalState());
        else if (choice == 2) sys->changeState(new HighPerformanceState());
        else if (choice == 3) sys->changeState(new SleepState());
        else if (choice == 4) sys->changeState(new LowPowerState());
        
        sys->log("[StateChange] Yeni Durum: " + sys->getStateName());
    }

    const char* getDescription() const { return "Sistem Durumunu Degistir (State)"; }
};

// --- SIMULASYON (TEST) ---
class SimulationCommand : public Command {
public:
    void execute() {
        SystemController* sys = SystemController::getInstance();
        std::cout << "\n--- SENARYO SIMULASYONU ---\n";
        std::cout << "[1] Hirsiz Var! (Kamera Hareket Algilar)\n";
        std::cout << "[2] Yangin Var! (Dedektor Duman Algilar)\n";
        std::cout << "Secim: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            sys->log("[Simulation] Hirsiz senaryosu tetiklendi.");
            if (sys->getCamera()) sys->getCamera()->detectMotion();
        } else if (choice == 2) {
            sys->log("[Simulation] Yangin senaryosu tetiklendi.");
            if (sys->getSmokeDetector()) sys->getSmokeDetector()->detectSmoke();
        }
    }
    const char* getDescription() const { return "Simulasyon Baslat (Hirsiz/Yangin)"; }
};

// --- ABOUT (REQ 2.1 - 9) ---
class AboutCommand : public Command {
public:
    void execute() {
        std::cout << "\n===================================" << std::endl;
        std::cout << "   MY SWEET HOME (MSH) v1.0" << std::endl;
        std::cout << "===================================" << std::endl;
        std::cout << "Developers:\n";
        std::cout << "- Ergun (Integrator)\n- Hamza (UI)\n- Murat (Factory)\n";
        std::cout << "- Yunus (Manager)\n- Mert (State/Mode)\n- Kayra (Logic)\n- Ali (Logger)\n";
        std::cout << "===================================" << std::endl;
    }
    const char* getDescription() const { return "Hakkinda (About)"; }
};

// --- MANUAL (REQ 2.1 - 8) ---
class ManualCommand : public Command {
public:
    void execute() {
        std::cout << "\n--- KULLANIM KILAVUZU ---\n";
        std::cout << "1. Cihaz ekleyerek sistemi kurun.\n";
        std::cout << "2. Modlari degistirerek (Sinema, Parti) ortami ayarlayin.\n";
        std::cout << "3. Simulasyon menusu ile Guvenlik sistemini test edin.\n";
        std::cout << "4. Log dosyasi (msh_log.txt) tum islemleri kaydeder.\n";
    }
    const char* getDescription() const { return "Yardim (Manual)"; }
};

// --- RAPOR ---
class ReportCommand : public Command {
public:
    void execute() {
        SystemController* sys = SystemController::getInstance();
        std::cout << "\n--- [MSH] SISTEM RAPORU ---" << std::endl;
        std::cout << "Mod: " << sys->getModeName() << std::endl;
        std::cout << "Durum: " << sys->getStateName() << std::endl;
        std::cout << "Performans: " << sys->getPerformance() << std::endl;
        if (sys->getDeviceManager()) {
            std::cout << "Toplam Cihaz: " << sys->getDeviceManager()->getDeviceCount() << std::endl;
        }
        std::cout << "---------------------------" << std::endl;
    }
    const char* getDescription() const { return "Sistem Raporu"; }
};

#endif