#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

// --- LOGIC MODULES ---
#include "Logic/SecuritySystem.h"
#include "Logic/DetectionSystem.h"
#include "Logic/HomeState.h"
#include "Logic/HomeStateMemento.h"

// --- DEVICES & UTILS ---
#include "Devices/Camera.h"
#include "Devices/SmokeDetector.h"
#include "Devices/ChineseLightAdapter.h"
#include "Utils/Logger.h"

// --- FORWARD DECLARATIONS ---
class Menu;
class DeviceManager; 

class SystemController {
private:
    static SystemController* instance;

    // Alt Sistemler
    Menu* menu;
    DeviceManager* deviceMgr;
    Logger* logger;
    
    SecuritySystem* securitySys;
    DetectionSystem* detectionSys;

    Camera* camera;
    SmokeDetector* smokeDetector;

    // --- STATE VARIABLES ---
    HomeState* currentState;
    HomeStateMemento* savedState;

    SystemController();

public:
    ~SystemController();
    static SystemController* getInstance();

    void init();
    void run();
    void shutdown();

    // Getterlar
    DeviceManager* getDeviceManager() const { return deviceMgr; }
    SecuritySystem* getSecuritySystem() const { return securitySys; }
    DetectionSystem* getDetectionSystem() const { return detectionSys; }
    
    Camera* getCamera() const { return camera; }
    SmokeDetector* getSmokeDetector() const { return smokeDetector; }

    // --- STATE YONETIMI ---
    void changeState(HomeState* newState);
    void saveCurrentState();
    void restorePreviousState();
    
    // Bilgi Fonksiyonlari
    std::string getStateName() const;
    std::string getPerformance() const; // Buna cpp'de govde ekledim
};

#endif