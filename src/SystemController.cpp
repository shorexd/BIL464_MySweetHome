#include "SystemController.h" 
#include <iostream>

// --- INCLUDE ---
#include "Devices/SamsungFactory.h"      
#include "Devices/DeviceManager.h"       
#include "Devices/DeviceIterator.h"      
#include "Logic/ConcreteStates.h"        
#include "Logic/ConcreteModes.h"         
#include "UI/Menu.h"                     
#include "UI/GeneralCommands.h"          
#include "Utils/FileLogTarget.h"         
#include "Utils/ChinaLogAdapter.h"       
#include "Utils/Logger.h"                

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
    // --- 1. LOGLAMA YAPILANDIRMASI (Ali - Strategy Pattern) ---
    if (logger) {
        // Eski hedefleri temizlemek icin bir mekanizma yoksa bile
        // Program basinda oldugumuz icin sorun degil.
        
        // A) Dosya Hedefi
        logger->attachTarget(new FileLogTarget("msh_log.txt"));
        
        // B) Cin Mali Cihaz Adaptoru
        logger->attachTarget(new ChinaLogAdapter());

        logger->log(INFO, "[System] SystemController initialized (Targets Attached).");
    } else {
        std::cout << "[Log-Sim] Logger not found!" << std::endl;
    }

    // --- 2. STATE & MODE BASLANGIC (Mert) ---
    if (currentState) currentState->enterState(this);
    if (currentMode) currentMode->apply(this);

    // --- 3. OBSERVER BAGLANTILARI (Kayra - KRITIK KISIM) ---
    // Bu satirlar olmazsa sensorler sinyal gonderir ama kimse duymaz!
    if (camera && securitySys) {
        camera->attach(securitySys);
        // std::cout << "[Debug] Kamera -> Guvenlik Sistemi baglandi.\n"; 
    }
    
    if (smokeDetector && detectionSys) {
        smokeDetector->attach(detectionSys);
        // std::cout << "[Debug] Dedektor -> Algilama Sistemi baglandi.\n";
    }

    // --- 4. SENSORLERI CIHAZ LISTESINE EKLE (Yunus & Senaryo Adim 4) ---
    // Rapor alindiginda bunlarin da gorunmesi icin
    if (deviceMgr) {
        // Eger zaten ekli degilse ekle (ID cakismasi olmamasi icin manager halleder ama biz pointer veriyoruz)
        // Not: SystemController constructor'da new ile olusturuldu.
        if (camera) deviceMgr->addDevice(camera);
        if (smokeDetector) deviceMgr->addDevice(smokeDetector);
    }

    // --- 5. MENU OLUSTURMA (Hamza) ---
    if (!menu) {
        menu = new Menu("MSH AKILLI EV YONETIM PANELI");
        
        menu->addCommand('1', new ReportCommand());
        menu->addCommand('2', new AddDeviceCommand());
        menu->addCommand('3', new RemoveDeviceCommand());
        menu->addCommand('4', new PowerControlCommand(true));
        menu->addCommand('5', new PowerControlCommand(false));
        menu->addCommand('6', new SetModeCommand());
        menu->addCommand('7', new SetStateCommand());
        menu->addCommand('8', new ManualCommand());
        menu->addCommand('9', new AboutCommand());
        menu->addCommand('!', new SimulationCommand()); 
    }

    std::cout << ">> SISTEM BASLATILDI (" << getStateName() << " - " << getModeName() << ")." << std::endl;
}

void SystemController::run() {
    if (menu) {
        menu->run();
    } else {
        std::cout << "HATA: Menu baslatilamadi!" << std::endl;
    }
    shutdown();
}

void SystemController::shutdown() {
    std::cout << ">> SISTEM KAPATILIYOR..." << std::endl;

    if (securitySys) { delete securitySys; securitySys = 0; }
    if (detectionSys) { delete detectionSys; detectionSys = 0; }
    
    // NOT: Camera ve SmokeDetector artik DeviceManager tarafindan da yonetiliyor olabilir.
    // Eger DeviceManager destructor'i bunlari siliyorsa, burada silmek double-free hatasi verebilir.
    // DeviceManager::addDevice pointer aliyor ve destructor'inda delete yapiyor.
    // O yuzden burada camera ve smokeDetector'u manuel silmemize gerek kalmadi (DeviceManager silecek).
    // Ancak guvenlik icin pointerlari sifirlayalim.
    camera = 0;
    smokeDetector = 0;
    
    // Yunus
    if (deviceMgr) { delete deviceMgr; deviceMgr = 0; }

    // Mert State
    if (currentState) { delete currentState; currentState = 0; }
    if (savedState) { delete savedState; savedState = 0; }

    // Mert Mode
    if (currentMode) { delete currentMode; currentMode = 0; }

    if (logger) {
        logger->log(INFO, "[System] System shutting down.");
    }
}

// --- STATE IMPLEMENTASYONLARI ---

void SystemController::changeState(HomeState* newState) {
    saveCurrentState(); 
    if (currentState) {
        currentState->exitState(this); 
        delete currentState;
    }
    currentState = newState;
    if (currentState) {
        currentState->enterState(this); 
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
