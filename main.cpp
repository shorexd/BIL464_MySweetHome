/**
 * DOSYA ADI main.cpp
 * GÖREVİ: Yazılan Güvenlik ve Algılama modüllerini TEST ETMEK.
 * NOT Bu dosya simülasyon amaçlıdır.
 */

#include <iostream>
#include "SecuritySystem.h"
#include "DetectionSystem.h"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   MY SWEET HOME - GUVENLIK TESTI" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;

    // 1. Sistemleri Oluşturuyoruz (Sanki cihazlar açılıyor)
    SecuritySystem* guvenlik = new SecuritySystem();
    DetectionSystem* algilama = new DetectionSystem();

    std::cout << std::endl << "--- SENARYO 1: HIRSIZ VAR! (Guvenlik Sistemi) ---" << std::endl;
    // Sanki Kamera "MOTION_DETECTED" sinyali göndermiş gibi sistemi tetikliyoruz:
    guvenlik->update("MOTION_DETECTED");

    std::cout << std::endl << "------------------------------------------------" << std::endl;

    std::cout << std::endl << "--- SENARYO 2: YANGIN VAR! (Algilama Sistemi) ---" << std::endl;
    // Sanki Dedektör "DANGER_DETECTED" sinyali göndermiş gibi sistemi tetikliyoruz:
    algilama->update("DANGER_DETECTED");

    std::cout << std::endl << "------------------------------------------------" << std::endl;

    std::cout << std::endl << "--- SENARYO 3: YANLIS ALARM ---" << std::endl;
    // Alakasız bir sinyal gelirse ne olur?
    guvenlik->update("KEDI_GECTI");

    std::cout << std::endl << "========================================" << std::endl;
    std::cout << "   TEST TAMAMLANDI." << std::endl;
    std::cout << "========================================" << std::endl;

    // Temizlik
    delete guvenlik;
    delete algilama;

    return 0;
}