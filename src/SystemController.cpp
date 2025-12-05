#include "SystemController.h" 
#include <iostream>

SystemController* SystemController::instance = 0;

SystemController* SystemController::getInstance() {
    if (!instance) {
        instance = new SystemController();
    }
    return instance;
}

SystemController::SystemController() {
    // --- GECICI NULL ATAMALARI ---
    logger = 0; 
    menu = 0;
    deviceMgr = 0;

    // --- LOGIC SISTEMLERI ---
    securitySys = new SecuritySystem();
    detectionSys = new DetectionSystem();

    // --- SENSORLER (YENI) ---
    camera = new Camera();
    smokeDetector = new SmokeDetector();
}

SystemController::~SystemController() {
    shutdown(); 
}

void SystemController::init() {
    std::cout << "[Log-Sim] System initializing..." << std::endl;

    // --- OBSERVER BAGLANTILARI (KRITIK NOKTA) ---
    // 1. Kamerayi Guvenlik Sistemine bagla (Abone yap)
    if (camera && securitySys) {
        camera->attach(securitySys);
    }

    // 2. Duman Dedektorunu Algilama Sistemine bagla
    if (smokeDetector && detectionSys) {
        smokeDetector->attach(detectionSys);
    }

    std::cout << ">> SISTEM BASLATILDI (Normal Mode)." << std::endl;
}

void SystemController::run() {
    bool running = true;
    
    while (running) {
        std::cout << "\n--- GECICI MENU ---" << std::endl;
        std::cout << "[10] Cikis Yap" << std::endl;
        std::cout << "[99] TEST: Hirsiz (Kamera)" << std::endl;
        std::cout << "[98] TEST: Yangin (Dedektor)" << std::endl;
        std::cout << "Secim: ";

        int choice;
        if (std::cin >> choice) {
            if (choice == 10) {
                running = false;
            } 
            else if (choice == 99) {
                // ARTIK GERCEK NESNE UZERINDEN TEST EDIYORUZ!
                if (camera) camera->detectMotion();
            } 
            else if (choice == 98) {
                if (smokeDetector) smokeDetector->detectSmoke();
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

    // Temizlik
    if (securitySys) { delete securitySys; securitySys = 0; }
    if (detectionSys) { delete detectionSys; detectionSys = 0; }
    
    // Sensorleri Temizle
    if (camera) { delete camera; camera = 0; }
    if (smokeDetector) { delete smokeDetector; smokeDetector = 0; }

    std::cout << "[Log-Sim] System Bye." << std::endl;
}