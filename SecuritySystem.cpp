/**
 * DOSYA ADI SecuritySystem.cpp
 * GÖREVİ: Güvenlik mantığının işlendiği mutfak.
 */

#include "SecuritySystem.h"

// 1. Sistem Başlarken
SecuritySystem::SecuritySystem() {
    std::cout << "[SecuritySystem] Guvenlik sistemi aktif edildi." << std::endl;
}

// 2. Sistem Kapanırken
SecuritySystem::~SecuritySystem() {
    std::cout << "[SecuritySystem] Guvenlik sistemi kapatiliyor." << std::endl;
}

// 3. Sinyal Geldiğinde (Asıl Olay!)
void SecuritySystem::update(const std::string& event_type) {
    std::cout << "[SecuritySystem] Sinyal alindi: " << event_type << std::endl;

    // Sadece "MOTION_DETECTED" (Hareket) varsa çalış (LLR-03)
    if (event_type == "MOTION_DETECTED") {
        std::cout << "[SecuritySystem] !!! TEHLIKE !!! Hareket algilandi." << std::endl;
        executeSecurityChain(); // Zinciri başlat!
    } else {
        std::cout << "[SecuritySystem] Bu sinyal guvenlik tehdidi degil." << std::endl;
    }
}

// 4. Zinciri Başlatma (Şimdilik taslak, sonra zincir kodunu bağlayacağız)
void SecuritySystem::executeSecurityChain() {
    std::cout << ">>> [ZINCIR BASLATILIYOR] Alarm -> Isik -> Polis (Kodlanacak) <<<" << std::endl;
}