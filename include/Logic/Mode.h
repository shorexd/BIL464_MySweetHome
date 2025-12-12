#ifndef MODE_H
#define MODE_H

#include <string>

// Forward Declaration: Sistemin yoneticisi SystemController
class SystemController;

class Mode {
public:
    virtual ~Mode() {}

    // LLR-M3: Arayuz fonksiyonlari (Context artik SystemController)
    virtual void apply(SystemController* context) = 0;
    virtual std::string getName() const = 0;
};

#endif