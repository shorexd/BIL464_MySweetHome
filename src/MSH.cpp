#include "../include/MSH.h"
#include "../include/ConcreteStates.h"
#include <iostream>

// LLR-S1: MSH başlatıldığında varsayılan NormalState olmalı
MSH::MSH() {
    currentState = new NormalState();
    currentState->enterState(this);
}

MSH::~MSH() {
    if (currentState) {
        delete currentState;
    }
}

// LLR-S5: changeState implementasyonu
void MSH::changeState(HomeState* newState) {
    if (currentState) {
        // 1. Eski state'in exit fonksiyonu
        currentState->exitState(this);
        // C++98'de memory management manueldir, eskiyi silmeliyiz
        delete currentState;
    }

    // 2. State'i güncelle
    currentState = newState;

    // 3. Yeni state'in enter fonksiyonu
    if (currentState) {
        currentState->enterState(this);
    }
}

// LLR-S7: Kullanıcı isteği ile tetiklenen eylem
void MSH::requestAction() {
    if (currentState) {
        currentState->handle(this);
    }
}

std::string MSH::getStateName() const {
    return currentState ? currentState->getName() : "No State";
}

// --- Memento İşlemleri ---
HomeStateMemento MSH::saveState() {
    std::cout << "--- [Sistem] Durum Kaydediliyor (" << currentState->getName() << ") ---" << std::endl;
    return HomeStateMemento(currentState);
}

void MSH::restoreState(const HomeStateMemento& memento) {
    HomeState* restoredState = memento.getState();
    std::cout << "--- [Sistem] Durum Geri Yukleniyor -> " << restoredState->getName() << " ---" << std::endl;
    changeState(restoredState);
}