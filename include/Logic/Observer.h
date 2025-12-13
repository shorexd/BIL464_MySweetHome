#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

// --- Observer Arayuzu (Gozlemci) ---
class IObserver {
public:
    virtual ~IObserver() {}
    virtual void update(const std::string& eventType) = 0;
};

// --- Subject Arayuzu (Yayin Yapan) ---
class ISubject {
public:
    virtual ~ISubject() {}
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify(const std::string& eventType) = 0;
};

#endif