#include "SystemController.h" 
#include <iostream>

// --- INCLUDE ---
#include "Devices/SamsungFactory.h"      // Murat
#include "Devices/DeviceManager.h"       // Yunus
#include "Devices/DeviceIterator.h"      // Yunus
#include "Logic/ConcreteStates.h"        // Mert (State)
#include "Logic/ConcreteModes.h"         // Mert (Mode)

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

    std::cout << ">> SISTEM BASLATILDI (" << getStateName() << " - " << getModeName() << ")." << std::endl;
}

void SystemController::run() {
    bool running = true;
    
    while (running) {
        // GECICI TEST MENU
        std::cout << "\n--- MSH KONTROL PANELI ---" << std::endl;
        std::cout << "DURUM: " << getStateName() << " | MOD: " << getModeName() << std::endl;
        std::cout << "PERFORMANS: " << getPerformance() << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "[10] Cikis Yap" << std::endl;
        std::cout << "[99] TEST: Hirsiz (Kamera)" << std::endl;
        std::cout << "[98] TEST: Yangin (Dedektor)" << std::endl;
        std::cout << "[96] TEST: Cihaz Yonetimi (TV Ekle/Kopyala)" << std::endl;
        std::cout << "[95] TEST: Durum Degistir (Uyku Moduna Gec)" << std::endl;
        std::cout << "[94] TEST: Mod Degistir (Sinema Modu - Isiklar Kapanir, TV Acilir)" << std::endl;
        std::cout << "Secim: ";

        int choice;
        if (std::cin >> choice) {
            if (choice == 10) {
                running = false;
            } 
            else if (choice == 99) { // Kayra Test
                if (camera) camera->detectMotion();
            } 
            else if (choice == 98) { // Kayra Test
                if (smokeDetector) smokeDetector->detectSmoke();
            }
            else if (choice == 96) { // Murat & Yunus Test
                std::cout << "[Test] Cihaz Fabrikasi..." << std::endl;
                SamsungFactory sf;
                Device* tv = sf.createTV();
                if(deviceMgr) {
                    int id = deviceMgr->addDevice(tv);
                    std::cout << "TV Eklendi. ID: " << id << std::endl;
                    deviceMgr->copyDevice(id); // Prototype Testi
                    std::cout << "TV Kopyalandi." << std::endl;
                }
            }
            else if (choice == 95) { // Mert State Test
                std::cout << "[Test] Uyku Durumuna Geciliyor..." << std::endl;
                changeState(new SleepState());
            }
            else if (choice == 94) { // Mert Mode Test
                std::cout << "[Test] Sinema Moduna Geciliyor..." << std::endl;
                // Once cihaz yoksa test icin ekleyelim ki etkiyi gorelim
                if (deviceMgr && deviceMgr->getDeviceCount() == 0) {
                     SamsungFactory sf;
                     deviceMgr->addDevice(sf.createTV());
                     std::cout << "(Test icin otomatik TV eklendi)" << std::endl;
                }
                changeMode(new CinemaMode());
            }
            else {
                std::cout << "Gecersiz secim." << std::endl;
            }
        } else {
             std::cin.clear();
             std::string temp;
             std::getline(std::cin, temp);
        }
    }
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