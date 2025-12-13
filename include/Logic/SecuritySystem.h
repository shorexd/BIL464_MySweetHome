#ifndef SECURITYSYSTEM_H
#define SECURITYSYSTEM_H

#include "Observer.h" // <--- EKLENDI: Artik IObserver'i buradan taniyor
#include <string>

// Observer Pattern: Observer (Gozlemci)
class SecuritySystem : public IObserver {
public:
    SecuritySystem();
    ~SecuritySystem();

    // IObserver Arayuzu
    void update(const std::string& eventType);

    // Chain of Responsibility Baslatici
    void executeSecurityChain();
};

#endif