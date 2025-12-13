#include "SystemController.h" 
#include <iostream>

// --- INCLUDE ---
#include "Devices/SamsungFactory.h"      // Murat
#include "Devices/DeviceManager.h"       // Yunus
#include "Devices/DeviceIterator.h"      // Yunus
#include "Logic/ConcreteStates.h"        // Mert (State)
#include "Logic/ConcreteModes.h"         // Mert (Mode)
#include "UI/Menu.h"              // hamza
#include "UI/GeneralCommands.h"   // hamza

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
        logger->open("msh_log.txt"); 
        logger->log("[System] SystemController initialized.");
    } else {
        std::cout << "[Log-Sim] System initializing..." << std::endl;
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
    
    // PDF REQ 2.1'e gore tam liste:
    menu->addCommand(new ReportCommand());          // [1] Status
    menu->addCommand(new AddDeviceCommand());       // [2] Add Device
    menu->addCommand(new RemoveDeviceCommand());    // [3] Remove Device
    menu->addCommand(new PowerControlCommand(true));  // [4] Power On
    menu->addCommand(new PowerControlCommand(false)); // [5] Power Off
    menu->addCommand(new SetModeCommand());         // [6] Change Mode
    menu->addCommand(new SetStateCommand());        // [7] Change State
    menu->addCommand(new ManualCommand());          // [8] Manual
    menu->addCommand(new AboutCommand());           // [9] About
    menu->addCommand(new SimulationCommand());      // [Ekstra] Test icin
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
        logger->log("[System] System shutting down.");
        logger->close();
    }
}

// --- STATE IMPLEMENTASYONLARI ---

void SystemController::changeState(HomeState* newState) {
    if (currentState) {
        currentState->exitState(this);
        delete currentState;
    }
    currentState = newState;
    if (currentState) currentState->enterState(this);
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