#include "UI/GeneralCommands.h"
#include "SystemController.h" 
// KRITIK DUZELTME: DeviceManager'i buraya ekledik!
#include "Devices/DeviceManager.h" 

#include "Devices/SamsungFactory.h"
#include "Devices/LGFactory.h"
#include "Devices/ChineseLightAdapter.h"
#include "Devices/Camera.h"
#include "Devices/SmokeDetector.h"
#include "Logic/ConcreteModes.h"
#include "Logic/ConcreteStates.h"
#include "Devices/DeviceIterator.h" 
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits> 

// Helper Implementasyonlari
std::string intToString(int val) {
    std::stringstream ss; ss << val; return ss.str();
}

void listDevices(SystemController* sys, int filterMode) {
    if (!sys->getDeviceManager()) return;

    std::string title = "TUM CIHAZLAR";
    if (filterMode == 1) title = "ACILABILIR CIHAZLAR (Su an Kapali)";
    if (filterMode == 2) title = "KAPATILABILIR CIHAZLAR (Su an Acik)";

    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "   " << title << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << " ID  | DURUM      | CIHAZ / MODEL       " << std::endl;
    std::cout << "---- | ---------- | ------------------- " << std::endl;

    DeviceIterator it = sys->getDeviceManager()->createIterator();
    bool empty = true;
    for (it.first(); it.hasNext(); it.next()) {
        Device* d = it.current();
        if (d) {
            bool power = d->getPowerState();
            bool broken = d->getBroken();
            
            if (!broken) {
                if (filterMode == 1 && power == true) continue; 
                if (filterMode == 2 && power == false) continue;
            }

            std::string status = "[KAPALI]";
            if (broken) status = "[ARIZALI]";
            else if (power) status = "[ ACIK ]";

            std::cout << " [" << d->getID() << "] | " << std::setw(10) << std::left << status << " | " << d->getName() << std::endl;
            empty = false;
        }
    }

    if (empty) {
        std::cout << "       (Listelenecek cihaz yok)      " << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}

// --- COMMAND IMPLEMENTASYONLARI ---

void AddDeviceCommand::execute() {
    SystemController* sys = SystemController::getInstance();
    if (!sys->getDeviceManager()) return;

    std::cout << "\n--- CIHAZ EKLEME SIHIRBAZI ---" << std::endl;
    std::cout << "[1] TV (Samsung/LG)\n[2] Akilli Lamba (Adapter)\n[3] Guvenlik Kamerasi\n[0] IPTAL\nSecim: ";
    int choice; std::cin >> choice;
    if (choice == 0) return;

    std::cout << "Kac adet?: ";
    int count; std::cin >> count;
    if(count < 1) count = 1;

    bool copyConfig = false;
    if (count > 1) {
        std::cout << "Ayarlar kopyalansin mi? (e/h): ";
        char c; std::cin >> c;
        if(c=='e'||c=='E') copyConfig = true;
    }

    Device* prototype = 0;
    std::string logMsg = "";

    if (choice == 1) { 
        std::cout << "Marka [1]Samsung [2]LG: "; int b; std::cin >> b;
        std::cout << "\n--- Modeller ---\n * QLED, OLED, NanoCell, UHD-4K\nModel: "; 
        std::string m; std::cin >> m;
        TVConfig config(m, "4K", 60);
        if (b == 1) prototype = SamsungFactory().createTV(config);
        else prototype = LGFactory().createTV(config);
        logMsg = "TV";
    } 
    else if (choice == 2) {
        prototype = new ChineseLightAdapter("SmartBulb-V2");
        logMsg = "Lamba";
    }
    else if (choice == 3) {
        prototype = new Camera();
        logMsg = "Kamera";
    }

    if (prototype) {
        int firstId = sys->getDeviceManager()->addDevice(prototype);
        std::cout << ">> BASARILI. ID: " << firstId << std::endl;
        sys->log("[Action] " + logMsg + " eklendi. ID: " + intToString(firstId));

        for (int i = 1; i < count; ++i) {
            if (copyConfig) {
                int newId = sys->getDeviceManager()->copyDevice(firstId);
                std::cout << ">> Kopya (" << (i+1) << ") ID: " << newId << "\n";
            } else {
                int newId = sys->getDeviceManager()->addDevice(prototype->clone());
                std::cout << ">> Yeni (" << (i+1) << ") ID: " << newId << "\n";
            }
        }
    }
}
const char* AddDeviceCommand::getDescription() const { return "Cihaz Ekle"; }

void RemoveDeviceCommand::execute() {
    SystemController* sys = SystemController::getInstance();
    listDevices(sys, 0); 
    std::cout << "Silinecek ID (0 = Iptal): ";
    int id; std::cin >> id;
    if (id == 0) return;

    if (sys->getDeviceManager()->removeDevice(id)) {
        std::cout << ">> Silindi." << std::endl;
        sys->log("Cihaz silindi ID: " + intToString(id));
    } else {
        std::cout << ">> Hata: ID yok." << std::endl;
    }
}
const char* RemoveDeviceCommand::getDescription() const { return "Cihaz Sil"; }

PowerControlCommand::PowerControlCommand(bool o) : on(o) {}
void PowerControlCommand::execute() {
    SystemController* sys = SystemController::getInstance();
    int filter = on ? 1 : 2;
    listDevices(sys, filter);

    std::cout << "Islem ID (0 = Hepsi / -1 = Iptal): ";
    int id; std::cin >> id;
    if (id == -1) return;

    DeviceIterator it = sys->getDeviceManager()->createIterator();
    bool found = false;
    
    for(it.first(); it.hasNext(); it.next()) {
        Device* d = it.current();
        bool matchesFilter = (on && !d->getPowerState()) || (!on && d->getPowerState());
        
        if (d && ((id == 0 && matchesFilter) || d->getID() == id)) {
            if (d->getBroken()) {
                std::cout << ">> [HATA] Cihaz ID " << d->getID() << " ARIZALI! Islem yapilamaz." << std::endl;
                std::cout << "   -> Lutfen teknik servisi arayin." << std::endl;
                continue; 
            }
            if(on) d->turnOn(); else d->turnOff();
            found = true;
        }
    }
    if (found) sys->log(on ? "Guc Acildi" : "Guc Kapatildi");
}
const char* PowerControlCommand::getDescription() const { return on ? "Cihaz Ac" : "Cihaz Kapat"; }

void SetModeCommand::execute() {
    SystemController* s = SystemController::getInstance();
    std::cout << "\n--- MOD ---\n[1]Normal [2]Cinema [3]Party [4]Evening [0]Iptal: ";
    int c; std::cin >> c;
    if(c==0) return;
    if(c==1) s->changeMode(new NormalMode());
    else if(c==2) s->changeMode(new CinemaMode());
    else if(c==3) s->changeMode(new PartyMode());
    else if(c==4) s->changeMode(new EveningMode());
    s->log("Mod: " + s->getModeName());
}
const char* SetModeCommand::getDescription() const { return "Mod Degistir"; }

void SetStateCommand::execute() {
    SystemController* s = SystemController::getInstance();
    std::cout << "\n--- STATE ---\n[1]Normal [2]HighPerf [3]Sleep [4]LowPower [5]Undo [0]Iptal: ";
    int c; std::cin >> c;
    if(c==0) return;
    if(c==1) s->changeState(new NormalState());
    else if(c==2) s->changeState(new HighPerformanceState());
    else if(c==3) s->changeState(new SleepState());
    else if(c==4) s->changeState(new LowPowerState());
    else if(c==5) s->restorePreviousState();
    s->log("Durum: " + s->getStateName());
}
const char* SetStateCommand::getDescription() const { return "Durum Degistir"; }

void ManualCommand::execute() { 
    std::cout << "\n==================================================" << std::endl;
    std::cout << "         MSH KULLANIM KILAVUZU (MANUAL)           " << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "1. BASLANGIC: Sistem 'Normal Mod' ile acilir." << std::endl;
    std::cout << "\n2. CIHAZ YONETIMI:" << std::endl;
    std::cout << "   - [2] Ekle: Marka ve Model secimi yapilir. (Factory Pattern)" << std::endl;
    std::cout << "   - [3] Sil: Listeden ID secilerek silinir. (Iterator Pattern)" << std::endl;
    std::cout << "   - [4/5] Guc: Sadece uygun durumdaki cihazlar listelenir." << std::endl;
    std::cout << "\n3. GUVENLIK SENARYOLARI (Chain of Resp.):" << std::endl;
    std::cout << "   - [!] Simulasyon > Hirsiz: Alarm -> Isik -> Polis (Kesintisiz)." << std::endl;
    std::cout << "   - [!] Simulasyon > Yangin: Alarm calar. Susturmak icin 'e' veya 'h'" << std::endl;
    std::cout << "     girisi beklenir (LLR-07). Susturulmazsa Itfaiye aranir." << std::endl;
    std::cout << "\n4. ARIZA YONETIMI:" << std::endl;
    std::cout << "   - [!] Simulasyon > Ariza: Cihazi bozar, kilitler ve listede [ARIZALI] yazar." << std::endl;
    std::cout << "==================================================" << std::endl;
}
const char* ManualCommand::getDescription() const { return "Yardim (Manual)"; }

void AboutCommand::execute() { 
    std::cout << "\n##################################################" << std::endl;
    std::cout << "           MY SWEET HOME (MSH) v1.0               " << std::endl;
    std::cout << "##################################################" << std::endl;
    std::cout << "GELISTIRICI EKIBI:" << std::endl;
    std::cout << "* Ergun (Entegrator)     - 220206012" << std::endl;
    std::cout << "* Hamza (UI & Command)   - 220206904" << std::endl;
    std::cout << "* Murat (Factory)        - 220206906" << std::endl;
    std::cout << "* Yunus (Device Manager) - 220206910" << std::endl;
    std::cout << "* Mert  (State & Memento)- 220206025" << std::endl;
    std::cout << "* Kayra (Logic & Chain)  - 220206018" << std::endl;
    std::cout << "* Ali   (Logger & Adap)  - 220206901" << std::endl;
    std::cout << "\nKULLANILAN PATTERNLAR:" << std::endl;
    std::cout << "1. Singleton, 2. Abstract Factory, 3. Factory Method" << std::endl;
    std::cout << "4. Adapter, 5. Observer, 6. State, 7. Command" << std::endl;
    std::cout << "8. Chain of Resp., 9. Iterator, 10. Memento" << std::endl;
    std::cout << "11. Strategy, 12. Facade, 13. Prototype" << std::endl;
    std::cout << "##################################################" << std::endl;
}
const char* AboutCommand::getDescription() const { return "Hakkinda (About)"; }

void ReportCommand::execute() { 
    SystemController* s = SystemController::getInstance();
    std::cout << "\n--- EV DURUM RAPORU ---" << std::endl;
    std::cout << "Mod: " << s->getModeName() << " | Durum: " << s->getStateName() << "\n";
    if(s->getDeviceManager()) listDevices(s, 0); 
}
const char* ReportCommand::getDescription() const { return "Sistem Raporu"; }

void SimulationCommand::execute() {
    SystemController* s = SystemController::getInstance();
    std::cout << "\n--- SIMULATOR ---\n";
    std::cout << "[1] Hirsiz (Kamera -> Alarm -> Isik -> Polis) [Otomatik]\n";
    std::cout << "[2] Yangin (Dedektor -> Alarm -> Soru -> Itfaiye) [Sorgulu]\n";
    std::cout << "[3] Ariza (Device Fail Sim.)\n";
    std::cout << "[0] Iptal\n";
    std::cout << "Secim: ";
    int c; std::cin >> c;
    
    std::cin.ignore(10000, '\n'); 

    if (c == 0) return;

    if(c==1) { 
        s->log("[Sim] Hirsiz senaryosu baslatildi."); 
        if(s->getCamera()) s->getCamera()->detectMotion(); 
    }
    else if(c==2) { 
        s->log("[Sim] Yangin senaryosu baslatildi."); 
        if(s->getSmokeDetector()) s->getSmokeDetector()->detectSmoke(); 
    }
    else if(c==3) {
        listDevices(s, 0); 
        std::cout << "Bozulacak Cihaz ID: "; 
        int id; std::cin >> id;
        std::cin.ignore(10000, '\n'); 

        if(s->getDeviceManager()) {
            Device* d = s->getDeviceManager()->findDevice(id);
            if(d) {
                d->setBroken(true);
                s->log("[Sim] Ariza bildirimi: ID " + intToString(id) + " bozuldu!");
                std::cout << ">> [ARIZA SIMULASYONU] Cihaz " << id << " (" << d->getName() << ") bozuldu. Durum: INACTIVE." << std::endl;
            } else {
                std::cout << ">> Hata: Gecersiz ID.\n";
            }
        }
    }
}
const char* SimulationCommand::getDescription() const { return "Simulasyon Baslat"; }