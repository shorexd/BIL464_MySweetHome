/**
 * DOSYA ADI DetectionSystem.h
 * ROLÜ: Somut Gözlemci (Concrete Observer) - YANGIN/GAZ İÇİN
 * GÖREVİ: Duman/Gaz algılandığında Algılama Zincirini (Detection Chain) tetikler.
 * İLGİLİ LLR LLR-04, LLR-06
 */

#ifndef DETECTIONSYSTEM_H
#define DETECTIONSYSTEM_H

#include "IObserver.h"
#include <string>

class DetectionSystem : public IObserver {
public:
    DetectionSystem();
    ~DetectionSystem();

    // Sensörden haber alma fonksiyonu
    void update(const std::string& event_type);

private:
    // Yangın senaryosunu (Alarm->Flaşör->İtfaiye) başlatacak fonksiyon
    void executeDetectionChain();
};

#endif // DETECTIONSYSTEM_H