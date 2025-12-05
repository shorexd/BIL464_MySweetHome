#ifndef CAMERA_H
#define CAMERA_H

#include "../Logic/ISubject.h"
#include <vector>
#include <string>

class Camera : public ISubject {
private:
    // Beni dinleyenlerin listesi (Guvenlik Sistemi vb.)
    std::vector<IObserver*> observers;

public:
    Camera();
    virtual ~Camera();

    // ISubject'ten gelen zorunlu fonksiyonlar
    void attach(IObserver* observer);
    void detach(IObserver* observer);
    void notify(const std::string& event_type);

    // Kameranin kendi isi
    void detectMotion();
};

#endif