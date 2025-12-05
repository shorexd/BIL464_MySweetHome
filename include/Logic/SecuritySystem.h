/**
 * DOSYA ADI SecuritySystem.h
 * ROLÜ: Somut Gözlemci (Concrete Observer)
 * GÖREVİ: Kameradan sinyal geldiğinde Güvenlik Zincirini tetikler.
 * İLGİLİ LLR LLR-02, LLR-03
 */

#ifndef SECURITYSYSTEM_H
#define SECURITYSYSTEM_H

#include "IObserver.h" // Sözleşmeyi bilmesi lazım
#include <string>
#include <iostream>

// ": public IObserver" -> "Ben Observer sözleşmesini imzaladım" demek.
class SecuritySystem : public IObserver {
public:
    SecuritySystem();  // Yapıcı (Başlangıç)
    ~SecuritySystem(); // Yıkıcı (Bitiş)

    // Sözleşme gereği bu fonksiyonu tanımlamak ZORUNDAYIZ:
    void update(const std::string& event_type);

private:
    // İleride yazacağımız Zincirleme Reaksiyonu (Alarm->Işık->Polis) başlatacak fonksiyon.
    void executeSecurityChain();
};

#endif // SECURITYSYSTEM_H