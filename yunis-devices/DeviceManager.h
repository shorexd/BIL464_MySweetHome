#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <vector>
#include <utility>
#include "../murat-devices/Device.h"
#include "DeviceIterator.h"

class DeviceManager
{
public:
    DeviceManager();
    ~DeviceManager();

    // Yeni cihaz ekle, benzersiz ID ver ve ID'yi döndür.
    // Hata olursa -1 döner.
    int addDevice(Device *device);

    // ID ile cihazı bul (yoksa 0 döner)
    Device *findDevice(int deviceId);

    // Cihazı listeden kaldır
    bool removeDevice(int deviceId);

    // Toplam cihaz sayısı
    int getDeviceCount() const;

    // Iterator üret
    DeviceIterator createIterator();

private:
    std::vector<std::pair<int, Device *>> m_devices;
    int m_nextId;

    bool idExists(int deviceId) const;
};

#endif
