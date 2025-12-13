#ifndef SMOKEDETECTOR_H
#define SMOKEDETECTOR_H

#include "Logic/Observer.h" // <--- DUZELTILDI (Path)
#include <string>
#include <vector>

// Observer Pattern: Subject
class SmokeDetector : public ISubject {
private:
    std::vector<IObserver*> observers;

public:
    SmokeDetector();
    virtual ~SmokeDetector();

    // ISubject Arayuzu
    void attach(IObserver* observer);
    void detach(IObserver* observer);
    void notify(const std::string& eventType);

    // Kendi Fonksiyonlari
    void detectSmoke();
    std::string getType() const; 
};

#endif