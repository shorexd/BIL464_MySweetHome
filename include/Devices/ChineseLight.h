#ifndef CHINESELIGHT_H
#define CHINESELIGHT_H

#include <string>

class ChineseLight {
private:
    std::string model;
public:
    // Sadece bildirim (Implementation .cpp dosyasinda olacak)
    explicit ChineseLight(const std::string& modelName);

    // Adapter'in bekledigi fonksiyon isimleri
    void switchOn_220V();
    void switchOff_220V();
};

#endif