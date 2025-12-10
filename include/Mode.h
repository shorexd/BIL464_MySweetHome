#ifndef MODE_H
#define MODE_H

#include <string>

class MSH; // Forward declaration

class Mode {
public:
    virtual ~Mode() {}

    // LLR-M3: Arayuz fonksiyonlari
    virtual void apply(MSH* context) = 0;
    virtual std::string getName() const = 0;
};

#endif