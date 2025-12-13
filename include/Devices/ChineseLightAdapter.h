#ifndef CHINESELIGHTADAPTER_H
#define CHINESELIGHTADAPTER_H

#include "Device.h"       
#include "ChineseLight.h" 
#include <string>

// Device sinifindan miras aliyor (Fixlendi)
class ChineseLightAdapter : public Device {
private:
    ChineseLight* adaptee;
    std::string modelName;
    int id;

public:
    explicit ChineseLightAdapter(const std::string& model);
    ChineseLightAdapter(const ChineseLightAdapter& other);
    ~ChineseLightAdapter();

    void turnOn();
    void turnOff();
    std::string getName() const;
    int getID() const;
    void setID(int newID);
    
    Device* clone() const;
};

#endif