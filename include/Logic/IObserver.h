/**
 * DOSYA ADI IObserver.h
 * ROLÜ: Gözlemci Arayüzü (Interface)
 * KİM KULLANACAK SecuritySystem, DetectionSystem (LLR-02)
 */

#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <string> // string kullanacağız

class IObserver {
public:
    // Sanal Yıkıcı (Virtual Destructor)
    // Neden var? Bu arayüzden türetilen sınıflar silinirken hafıza sızıntısı olmasın diye.
    virtual ~IObserver() {}

    // HABER ALMA FONKSİYONU (SÖZLEŞME MADDESİ)
    // virtual ... = 0  -> "Bu fonksiyonu sen doldurmak zorundasın"
    // event_type       -> Gelen haberin türü (Örn: "MOTION_DETECTED")
    virtual void update(const std::string& event_type) = 0;
};

#endif // IOBSERVER_H