// include/Devices/ChineseLight.h
#ifndef CHINESE_LIGHT_H
#define CHINESE_LIGHT_H

#include <string>

// Uyumsuz (third-party) Çin malı ışık sınıfı.
// Interface'i normal Device arayüzünden farklı olacak.
class ChineseLight {
public:
  explicit ChineseLight(const std::string &modelName);

  // Kendi özel fonksiyon isimleri:
  void turnOnLamp();
  void turnOffLamp();

  // 0..3 arası seviye (0=kapalı, 3=en parlak)
  void setLevel(int level);

  bool isLampOn() const;
  int level() const;
  const std::string &model() const;

private:
  std::string m_model;
  bool m_on;
  int m_level; // 0..3
};

#endif // CHINESE_LIGHT_H
