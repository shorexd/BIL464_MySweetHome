#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <vector>
#include <utility>
#include "Device.h"          
#include "DeviceIterator.h"  

class DeviceManager {
public:
    DeviceManager();
    ~DeviceManager();

    // Cihaz Ekleme (LLR-3: Iterator kontrolu iceride yapilacak)
    int addDevice(Device *device);

    // Cihaz Bulma
    Device *findDevice(int deviceId);

    // Cihaz Silme (LLR-7)
    bool removeDevice(int deviceId);

    // Cihaz Kopyalama (LLR-4, LLR-6)
    int copyDevice(int deviceId);

    // LLR-8: Sistem acilisinda yukleme (EKSİKTİ, EKLENDİ)
    void loadDevicesFromStorage();

    // LLR-9: Disari iterator verme
    DeviceIterator createIterator();
    
    int getDeviceCount() const;

private:
    std::vector<std::pair<int, Device *> > m_devices;
    int m_nextId;

    // LLR-3: ID kontrolunu Iterator ile yapacagiz
    bool checkIdWithIterator(int deviceId);
};

#endif