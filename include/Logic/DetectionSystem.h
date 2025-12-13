#ifndef DETECTIONSYSTEM_H
#define DETECTIONSYSTEM_H

#include "Observer.h" // <--- EKLENDI
#include <string>

// Observer Pattern: Observer (Gozlemci)
class DetectionSystem : public IObserver {
public:
    DetectionSystem();
    ~DetectionSystem();

    // IObserver Arayuzu
    void update(const std::string& eventType);

    // Chain of Responsibility Baslatici
    void executeDetectionChain();
};

#endif