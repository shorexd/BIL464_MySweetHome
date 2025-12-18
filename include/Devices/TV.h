#ifndef TV_H
#define TV_H

#include "Device.h"
#include <string>
#include <sstream> // EKLENDI: C++98 string donusumu icin sart

class TV : public Device {
protected:
    int currentChannel;
    // LLR-03: Eklenen Ozellikler
    std::string resolution;
    int fps;
    std::string brand;

public:
    TV() : currentChannel(1), resolution("1080p"), fps(60), brand("Generic") {}
    
    virtual void setChannel(int ch) = 0;

    // Setterlar (Factory bunlari kullanacak)
    void setResolution(const std::string& res) { resolution = res; }
    void setFPS(int f) { fps = f; }
    void setBrand(const std::string& b) { brand = b; }
    
    // DUZELTME: std::to_string yerine stringstream kullanildi (C++98 Uyumlu)
    std::string getDetails() const { 
        std::stringstream ss;
        ss << fps;
        return brand + " " + resolution + " @" + ss.str() + "Hz"; 
    }
};

#endif