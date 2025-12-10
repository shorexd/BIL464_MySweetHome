#ifndef CONCRETEMODES_H
#define CONCRETEMODES_H

#include "Mode.h"

// LLR-M4: Tum siniflar Mode arayuzunden turetilmeli

class NormalMode : public Mode {
public:
    void apply(MSH* context);
    std::string getName() const;
};

class EveningMode : public Mode {
public:
    void apply(MSH* context);
    std::string getName() const;
};

class PartyMode : public Mode {
public:
    void apply(MSH* context);
    std::string getName() const;
};

class CinemaMode : public Mode {
public:
    void apply(MSH* context);
    std::string getName() const;
};

#endif