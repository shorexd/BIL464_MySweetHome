#include "Devices/ChineseLightAdapter.h"
#include <iostream>

ChineseLightAdapter::ChineseLightAdapter(const std::string& model) {
    this->modelName = model;
    this->adaptee = new ChineseLight(model); 
    this->id = 0;
    
    // FIX: Ismi Base Class'a kaydediyoruz -> Unknown sorunu cozuldu
    this->setName("SmartBulb (" + model + ")");
}

// Copy Constructor
ChineseLightAdapter::ChineseLightAdapter(const ChineseLightAdapter& other) {
    this->modelName = other.modelName;
    this->id = other.id;
    this->adaptee = new ChineseLight(other.modelName); 
    
    // Kopyalarken de ismi tasiyoruz
    this->setName("SmartBulb (" + other.modelName + ")");
}

ChineseLightAdapter::~ChineseLightAdapter() {
    if (adaptee) {
        delete adaptee;
    }
}

void ChineseLightAdapter::turnOn() {
    if (adaptee) adaptee->switchOn_220V();
    this->isOn = true; // Durum guncelleme
}

void ChineseLightAdapter::turnOff() {
    if (adaptee) adaptee->switchOff_220V();
    this->isOn = false;
}

int ChineseLightAdapter::getID() const {
    return id;
}

void ChineseLightAdapter::setID(int newID) {
    this->id = newID;
}

Device* ChineseLightAdapter::clone() const {
    return new ChineseLightAdapter(*this);
}