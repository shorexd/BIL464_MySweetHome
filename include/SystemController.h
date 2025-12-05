#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include "../Logic/SecuritySystem.h"
#include "../Logic/DetectionSystem.h"

// YENI EKLENENLER:
#include "../Devices/Camera.h"
#include "../Devices/SmokeDetector.h"

// Forward Declaration
class Menu;
class DeviceManager;
class Logger;

class SystemController {
private:
    static SystemController* instance;

    Menu* menu;
    DeviceManager* deviceMgr;
    Logger* logger;
    
    SecuritySystem* securitySys;
    DetectionSystem* detectionSys;

    // YENI EKLENEN SENSORLER
    Camera* camera;
    SmokeDetector* smokeDetector;

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
    
    // Test icin getterlar
    Camera* getCamera() const { return camera; }
    SmokeDetector* getSmokeDetector() const { return smokeDetector; }
};

#endif