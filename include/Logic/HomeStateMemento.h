#ifndef HOMESTATEMEMENTO_H
#define HOMESTATEMEMENTO_H

#include "HomeState.h"
#include <cstddef> // NULL icin

class HomeStateMemento {
private:
    HomeState* storedState;

public:
    // 1. Constructor
    HomeStateMemento(HomeState* state) {
        if (state) {
            storedState = state->clone();
        } else {
            storedState = NULL;
        }
    }

    // 2. Copy Constructor (Kopyalama Kurucusu)
    HomeStateMemento(const HomeStateMemento& other) {
        if (other.storedState) {
            storedState = other.storedState->clone();
        } else {
            storedState = NULL;
        }
    }

    // 3. Assignment Operator (Atama Operatoru) - EKLENEN KISIM
    // "backup = system->saveState()" yapildiginda burasi calisir.
    HomeStateMemento& operator=(const HomeStateMemento& other) {
        // Kendine atama kontrolu (backup = backup)
        if (this != &other) {
            // Once elimizdeki eski hafizayi temizleyelim
            if (storedState) {
                delete storedState;
            }

            // Simdi yeni veriyi derin kopyalayalim (Deep Copy)
            if (other.storedState) {
                storedState = other.storedState->clone();
            } else {
                storedState = NULL;
            }
        }
        return *this;
    }

    // 4. Destructor (Yikici)
    ~HomeStateMemento() {
        if (storedState) {
            delete storedState;
        }
    }

    HomeState* getState() const {
        return storedState ? storedState->clone() : NULL;
    }
};

#endif