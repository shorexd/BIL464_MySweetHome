// src/ChineseLightAdapter.cpp
#include "Devices/ChineseLightAdapter.h"
#include <sstream>

ChineseLightAdapter::ChineseLightAdapter(const std::string& modelName)
    : m_light(modelName)
{
    Logger::getInstance().log(
        "ChineseLightAdapter created for model: " + modelName);
}

void ChineseLightAdapter::turnOn()
{
    m_light.turnOnLamp();

    std::ostringstream oss;
    oss << "ChineseLight (" << m_light.model() << ") turned ON at level "
        << m_light.level() << " (" << currentPercent() << "%)";
    Logger::getInstance().log(oss.str());
}

void ChineseLightAdapter::turnOff()
{
    m_light.turnOffLamp();

    Logger::getInstance().log(
        "ChineseLight (" + m_light.model() + ") turned OFF");
}

void ChineseLightAdapter::setBrightnessPercent(int percent)
{
    int level = levelFromPercent(percent);
    m_light.setLevel(level);

    std::ostringstream oss;
    oss << "ChineseLight (" << m_light.model()
        << ") brightness set to " << percent
        << "% (level " << m_light.level() << ")";
    Logger::getInstance().log(oss.str());
}

bool ChineseLightAdapter::isOn() const
{
    return m_light.isLampOn();
}

int ChineseLightAdapter::currentPercent() const
{
    return percentFromLevel(m_light.level());
}

int ChineseLightAdapter::levelFromPercent(int percent) const
{
    if (percent <= 0)  return 0;
    if (percent <= 33) return 1;
    if (percent <= 66) return 2;
    return 3; // 67..100
}

int ChineseLightAdapter::percentFromLevel(int level) const
{
    switch (level) {
    case 0: return 0;
    case 1: return 25;
    case 2: return 60;
    case 3: return 100;
    default: return 0;
    }
}
