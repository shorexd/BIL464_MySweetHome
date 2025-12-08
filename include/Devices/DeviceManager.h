#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <vector>
#include <utility>
#include "Device.h"          // Duzeltildi
#include "DeviceIterator.h"  // Duzeltildi

class DeviceManager {
public:
    DeviceManager();
    ~DeviceManager();

    // Cihaz Ekleme
    int addDevice(Device *device);

    // Cihaz Bulma
    Device *findDevice(int deviceId);

    // Cihaz Silme
    bool removeDevice(int deviceId);

    // --- PROTOTYPE PATTERN (Yunus'un eksigi tamamlandi) ---
    // Var olan bir cihazi kopyalar
    int copyDevice(int deviceId);

    // Iterator
    DeviceIterator createIterator();
    
    // Test icin toplam sayi
    int getDeviceCount() const;

private:
    std::vector<std::pair<int, Device *> > m_devices;
    int m_nextId;

    bool idExists(int deviceId) const;
};

#endif