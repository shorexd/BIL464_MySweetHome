#ifndef SMOKEDETECTOR_H
#define SMOKEDETECTOR_H

#include "../Logic/ISubject.h"
#include <vector>
#include <string>

class SmokeDetector : public ISubject {
private:
    std::vector<IObserver*> observers;

public:
    SmokeDetector();
    virtual ~SmokeDetector();

    void attach(IObserver* observer);
    void detach(IObserver* observer);
    void notify(const std::string& event_type);

    // Dedektorun kendi isi
    void detectSmoke();
};

#endif