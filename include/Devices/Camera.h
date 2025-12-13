#ifndef CAMERA_H
#define CAMERA_H

#include "Logic/Observer.h" // <--- DUZELTILDI (Path)
#include <string>
#include <vector>

// Observer Pattern: Subject (Yayin yapan)
class Camera : public ISubject {
private:
    std::vector<IObserver*> observers;

public:
    Camera();
    virtual ~Camera();

    // ISubject Arayuzu
    void attach(IObserver* observer);
    void detach(IObserver* observer);
    void notify(const std::string& eventType);

    // Kendi Fonksiyonlari
    void detectMotion();
    std::string getType() const;
};

#endif