#include "Devices/ChineseLightAdapter.h"
#include <iostream>

ChineseLightAdapter::ChineseLightAdapter(const std::string& model) {
    this->modelName = model;
    // FIX: Constructor artik parametre aliyor
    this->adaptee = new ChineseLight(model); 
    this->id = 0;
}

// Copy Constructor
ChineseLightAdapter::ChineseLightAdapter(const ChineseLightAdapter& other) {
    this->modelName = other.modelName;
    this->id = other.id;
    // FIX: Kopyalarken de parametre gonderiyoruz
    this->adaptee = new ChineseLight(other.modelName); 
}

ChineseLightAdapter::~ChineseLightAdapter() {
    if (adaptee) {
        delete adaptee;
    }
}

void ChineseLightAdapter::turnOn() {
    if (adaptee) adaptee->switchOn_220V(); 
}

void ChineseLightAdapter::turnOff() {
    if (adaptee) adaptee->switchOff_220V();
}

std::string ChineseLightAdapter::getName() const {
    return "SmartBulb (" + modelName + ")";
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