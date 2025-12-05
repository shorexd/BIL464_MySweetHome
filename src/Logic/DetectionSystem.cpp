/**
 * DOSYA ADI DetectionSystem.cpp
 * GÖREVİ: Yangın/Gaz senaryosunun yönetildiği yer.
 */

#include "DetectionSystem.h"
#include <iostream>

// Kullanacağımız Zincir Halkaları
#include "AlarmAction.h"
#include "FlashLightAction.h"      // Security'den farklı! (Normal ışık değil, flaşör)
#include "CallFireStationAction.h" // Security'den farklı! (Polis değil, itfaiye)

DetectionSystem::DetectionSystem() {
    std::cout << "[DetectionSystem] Algilama sistemi (Yangin/Gaz) aktif edildi." << std::endl;
}

DetectionSystem::~DetectionSystem() {
    std::cout << "[DetectionSystem] Algilama sistemi kapatiliyor." << std::endl;
}

void DetectionSystem::update(const std::string& event_type) {
    // Sadece "DANGER_DETECTED" (Tehlike) varsa çalış (LLR-04)
    if (event_type == "DANGER_DETECTED") {
        std::cout << "[DetectionSystem] !!! ACIL DURUM !!! Duman/Gaz algilandi." << std::endl;
        executeDetectionChain();
    }
}

void DetectionSystem::executeDetectionChain() {
    std::cout << ">>> [ZINCIR KURULUYOR] Alarm -> Flasor -> Itfaiye <<<" << std::endl;

    // 1. Halkaları Oluştur
    AbstractActionHandler* alarm = new AlarmAction();
    AbstractActionHandler* flasher = new FlashLightAction();
    AbstractActionHandler* fireDept = new CallFireStationAction();

    // 2. Zinciri Bağla (Alarm -> Flaşör -> İtfaiye)
    alarm->setNext(flasher)->setNext(fireDept);

    // 3. Zinciri Başlat ("DETECTION_CHAIN" koduyla)
    // Bu kod sayesinde FlashLight çalışacak, LightOn çalışmayacak.
    alarm->handle("DETECTION_CHAIN");

    // 4. Temizlik
    delete alarm;
    delete flasher;
    delete fireDept;
    
    std::cout << ">>> [ZINCIR TAMAMLANDI] Acil durum protokolu sona erdi. <<<" << std::endl;
}