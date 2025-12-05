// include/Devices/ChineseLightAdapter.h
#ifndef CHINESE_LIGHT_ADAPTER_H
#define CHINESE_LIGHT_ADAPTER_H

#include <string>
#include "Devices/ChineseLight.h"
#include "Logger.h"

// Adapter: ChineseLight'ın arayüzünü sisteme uyumlu hale getirir.
class ChineseLightAdapter {
public:
    explicit ChineseLightAdapter(const std::string& modelName);

    // Sistemin kullanacağı arayüz:
    void turnOn();                         // Işığı aç
    void turnOff();                        // Işığı kapat
    void setBrightnessPercent(int percent);// 0..100 arası parlaklık

    bool isOn() const;
    int  currentPercent() const;           // 0..100

private:
    // Yüzdelik değeri Çin cihazının 0..3 seviyesine çevir
    int levelFromPercent(int percent) const;
    // 0..3 seviyesini yaklaşık yüzdeye çevir
    int percentFromLevel(int level) const;

    // Gerçek Çin malı cihaz (adaptee)
    ChineseLight m_light;
};

#endif // CHINESE_LIGHT_ADAPTER_H
