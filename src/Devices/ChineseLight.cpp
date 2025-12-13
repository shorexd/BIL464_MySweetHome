#include "Devices/ChineseLight.h"
#include <iostream>

// Constructor Implementasyonu
ChineseLight::ChineseLight(const std::string& modelName) {
    this->model = modelName;
}

// Fonksiyon Implementasyonlari
void ChineseLight::switchOn_220V() {
    std::cout << "[ChineseLight " << model << "] Isiklar Acildi (220V)!" << std::endl;
}

void ChineseLight::switchOff_220V() {
    std::cout << "[ChineseLight " << model << "] Isiklar Kapandi." << std::endl;
}