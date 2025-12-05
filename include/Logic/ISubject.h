/**
 * DOSYA ADI ISubject.h
 * ROLÜ: Konu (Sinyal Kaynağı) Arayüzü
 * KİM KULLANACAK Camera, SmokeGasDetector (LLR-01)
 */

#ifndef ISUBJECT_H
#define ISUBJECT_H

#include "IObserver.h" // IObserver'ı tanımak zorunda, çünkü onları listeye alacak.

class ISubject {
public:
    virtual ~ISubject() {}

    // 1. ABONE EKLE (attach)
    // "Beni dinlemek isteyen gözlemci (observer) buraya gelsin."
    virtual void attach(IObserver* observer) = 0;

    // 2. ABONE SİL (detach)
    // "Artık beni dinlemek istemeyen listeden çıksın."
    virtual void detach(IObserver* observer) = 0;

    // 3. HERKESE HABER VER (notify)
    // "Olay oldu! Listedeki herkesin update() butonuna bas."
    virtual void notify(const std::string& event_type) = 0;
};

#endif // ISUBJECT_H