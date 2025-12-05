// src/ChineseLight.cpp
#include "Devices/ChineseLight.h"
#include <iostream>

ChineseLight::ChineseLight(const std::string &modelName)
    : m_model(modelName), m_on(false), m_level(0) {}

void ChineseLight::turnOnLamp() {
  m_on = true;
  if (m_level == 0) {
    m_level = 1; // Açılırken en azından düşük seviye
  }
  std::cout << "[ChineseLight] " << m_model << " lamp ON at level "
            << m_level << "\n";
}

void ChineseLight::turnOffLamp() {
  m_on = false;
  std::cout << "[ChineseLight] " << m_model << " lamp OFF\n";
}

void ChineseLight::setLevel(int level) {
  if (level < 0)
    level = 0;
  if (level > 3)
    level = 3;
  m_level = level;

  if (m_on) {
    std::cout << "[ChineseLight] " << m_model
              << " level set to " << m_level << "\n";
  }
}

bool ChineseLight::isLampOn() const { return m_on; }

int ChineseLight::level() const { return m_level; }

const std::string &ChineseLight::model() const { return m_model; }
