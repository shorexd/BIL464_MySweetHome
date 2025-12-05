/**
 * DOSYA ADI SecuritySystem.cpp (GÜNCELLENMİŞ HALİ)
 * GÖREVİ: Zincirin kurulduğu ve başlatıldığı yer.
 */

#include "SecuritySystem.h"
// Zincir halkalarını içeri alıyoruz
#include "AlarmAction.h"
#include "LightOnAction.h"
#include "CallPoliceAction.h"

SecuritySystem::SecuritySystem() {
    std::cout << "[SecuritySystem] Guvenlik sistemi aktif edildi." << std::endl;
}

SecuritySystem::~SecuritySystem() {
    std::cout << "[SecuritySystem] Guvenlik sistemi kapatiliyor." << std::endl;
}

void SecuritySystem::update(const std::string& event_type) {
    std::cout << "[SecuritySystem] Sinyal alindi: " << event_type << std::endl;

    if (event_type == "MOTION_DETECTED") {
        std::cout << "[SecuritySystem] !!! TEHLIKE !!! Hareket algilandi." << std::endl;
        executeSecurityChain(); 
    } else {
        std::cout << "[SecuritySystem] Bu sinyal guvenlik tehdidi degil." << std::endl;
    }
}

// İŞTE SİHİR BURADA GERÇEKLEŞİYOR!
void SecuritySystem::executeSecurityChain() {
    std::cout << ">>> [ZINCIR KURULUYOR] Alarm -> Isik -> Polis <<<" << std::endl;

    // 1. Halkaları Oluştur (Heap bellekte)
    AbstractActionHandler* alarm = new AlarmAction();
    AbstractActionHandler* light = new LightOnAction();
    AbstractActionHandler* police = new CallPoliceAction();

    // 2. Zinciri Bağla (Alarm -> Işık -> Polis)
    alarm->setNext(light)->setNext(police);

    // 3. Zinciri Başlat ("SECURITY_CHAIN" koduyla)
    // Bu kod sayesinde LightOn çalışacak ama FlashLight çalışmayacak.
    alarm->handle("SECURITY_CHAIN");

    // 4. Temizlik (Memory Cleanup) - İşi bitenleri siliyoruz
    delete alarm;
    delete light;
    delete police;
    
    std::cout << ">>> [ZINCIR TAMAMLANDI] Guvenlik protokolu sona erdi. <<<" << std::endl;
}