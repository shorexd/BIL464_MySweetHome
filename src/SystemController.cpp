#include "SystemController.h" 
#include <iostream>

// --- INCLUDE ---
#include "Devices/SamsungFactory.h"      // Murat
#include "Devices/DeviceManager.h"       // Yunus
#include "Devices/DeviceIterator.h"      // Yunus
#include "Logic/ConcreteStates.h"        // Mert (State)
#include "Logic/ConcreteModes.h"         // Mert (Mode)
#include "UI/Menu.h"                     // hamza
#include "UI/GeneralCommands.h"          // hamza
#include "Utils/FileLogTarget.h"         // Ali
#include "Utils/ChinaLogAdapter.h"       // Ali
#include "Utils/Logger.h"                // Ali

SystemController* SystemController::instance = 0;

SystemController* SystemController::getInstance() {
    if (!instance) {
        instance = new SystemController();
    }
    return instance;
}

SystemController::SystemController() {
    // 1. Logger (Ali)
    logger = &Logger::getInstance(); 

    // 2. Menu (Hamza - Henuz yok)
    menu = 0;

    // 3. DeviceManager (Yunus)
    deviceMgr = new DeviceManager(); 

    // 4. State (Mert) - Varsayilan NormalState
    currentState = new NormalState();
    savedState = 0;

    // 5. Mode (Mert) - Varsayilan NormalMode
    currentMode = new NormalMode();

    // 6. Logic (Kayra)
    securitySys = new SecuritySystem();
    detectionSys = new DetectionSystem();

    // 7. Sensors
    camera = new Camera();
    smokeDetector = new SmokeDetector();
}

SystemController::~SystemController() {
    shutdown(); 
}

void SystemController::init() {
    // Log acilisi
    if (logger) {
        // Eski 'open' metodu gitti.
        
        // A) Dosya Hedefi (FileLogTarget)
        logger->attachTarget(new FileLogTarget("msh_log.txt"));
        
        // B) Cin Mali Cihaz Adaptoru (ChinaLogAdapter)
        logger->attachTarget(new ChinaLogAdapter());

        // Ilk Logu atiyok
        logger->log(INFO, "[System] SystemController initialized (Targets Attached).");
    } else {
        std::cout << "[Log-Sim] Logger not found!" << std::endl;
    }

    // State Giris
    if (currentState) currentState->enterState(this);
    
    // Mode Uygula (Baslangic ayarlari)
    if (currentMode) currentMode->apply(this);

    // Observer Baglantilari
    if (camera && securitySys) camera->attach(securitySys);
    if (smokeDetector && detectionSys) smokeDetector->attach(detectionSys);

    if (!menu) {
        menu = new Menu("MSH AKILLI EV YONETIM PANELI");
        
        // REQ1 ve LLR-03'e uygun 'key' atamalari:
        menu->addCommand('1', new ReportCommand());
        menu->addCommand('2', new AddDeviceCommand());
        menu->addCommand('3', new RemoveDeviceCommand());
        menu->addCommand('4', new PowerControlCommand(true));
        menu->addCommand('5', new PowerControlCommand(false));
        menu->addCommand('6', new SetModeCommand());
        menu->addCommand('7', new SetStateCommand());
        menu->addCommand('8', new ManualCommand());
        menu->addCommand('9', new AboutCommand());
        menu->addCommand('!', new SimulationCommand()); // Test icin unlem
    }

    std::cout << ">> SISTEM BASLATILDI (" << getStateName() << " - " << getModeName() << ")." << std::endl;
}

void SystemController::run() {
    // Artik karmasik switch-case yok!
    // Tum yetki Menu objesinde.
    if (menu) {
        menu->run();
    } else {
        std::cout << "HATA: Menu baslatilamadi!" << std::endl;
    }
    
    // Menu'den donduysek (0'a basildiysa) kapat
    shutdown();
}

void SystemController::shutdown() {
    std::cout << ">> SISTEM KAPATILIYOR..." << std::endl;

    if (securitySys) { delete securitySys; securitySys = 0; }
    if (detectionSys) { delete detectionSys; detectionSys = 0; }
    if (camera) { delete camera; camera = 0; }
    if (smokeDetector) { delete smokeDetector; smokeDetector = 0; }
    
    // Yunus
    if (deviceMgr) { delete deviceMgr; deviceMgr = 0; }

    // Mert State
    if (currentState) { delete currentState; currentState = 0; }
    if (savedState) { delete savedState; savedState = 0; }

    // Mert Mode
    if (currentMode) { delete currentMode; currentMode = 0; }

    if (logger) {
        // Loglama sistemine son mesaji birakiyoruz.
        logger->log(INFO, "[System] System shutting down.");
        
        // FIX: logger->close() KALDIRILDI. 
        // Logger Singleton oldugu icin program bitince destructor'i 
        // otomatik calisacak ve dosyalari (Targets) temizleyip kapatacak.
    }
}

// --- STATE IMPLEMENTASYONLARI ---

void SystemController::changeState(HomeState* newState) {
    // LLR-S8: State degisimi oncesinde snapshot al (Memento)
    // Bu sayede "Previous" komutu calisabilir.
    // Ancak restore ederken tekrar kaydetmemek icin kontrol eklenebilir
    // ama basit Memento yapisinda her degisim bir kayit olusturur (Toggle mantigi).
    saveCurrentState(); 

    if (currentState) {
        currentState->exitState(this); // LLR-S5: Eski state exit
        delete currentState;
    }
    
    currentState = newState;
    
    if (currentState) {
        currentState->enterState(this); // LLR-S5: Yeni state enter
    }
}

void SystemController::saveCurrentState() {
    if (savedState) delete savedState;
    if (currentState) {
        std::cout << ">> Durum Kaydediliyor..." << std::endl;
        savedState = new HomeStateMemento(currentState);
    }
}

void SystemController::restorePreviousState() {
    if (savedState) {
        std::cout << ">> Eski Durum Yukleniyor..." << std::endl;
        HomeState* oldState = savedState->getState();
        changeState(oldState);
    } else {
        std::cout << "[Hata] Kayitli durum yok!" << std::endl;
    }
}

std::string SystemController::getStateName() const {
    return currentState ? currentState->getName() : "Unknown";
}

std::string SystemController::getPerformance() const {
    return currentState ? currentState->getPerformance() : "N/A";
}

// --- MODE IMPLEMENTASYONLARI ---

void SystemController::changeMode(Mode* newMode) {
    if (currentMode) {
        delete currentMode;
    }
    currentMode = newMode;
    
    if (currentMode) {
        std::cout << "\n*** MOD DEGISTIRILDI: " << currentMode->getName() << " ***" << std::endl;
        currentMode->apply(this);
    }
}

std::string SystemController::getModeName() const {
    return currentMode ? currentMode->getName() : "No Mode";
}

void SystemController::log(const std::string& message) {
    if (logger) {
        logger->log(message);
    }
}