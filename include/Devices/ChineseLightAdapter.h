#ifndef CHINESELIGHTADAPTER_H
#define CHINESELIGHTADAPTER_H

#include "Device.h"       
#include "ChineseLight.h" 
#include <string>

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
    
    // NOT: getName() BURADAN KALDIRILDI (Base class kullanilacak)
    
    int getID() const;
    void setID(int newID);
    
    Device* clone() const;
};

#endif