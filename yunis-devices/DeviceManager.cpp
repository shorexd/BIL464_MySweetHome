#include "Device.h"

DeviceManager::DeviceManager()
    : m_nextId(1)
{
}

DeviceManager::~DeviceManager()
{
    // Program kapanırken tüm cihazları serbest bırak
    for (int i = 0; i < (int)m_devices.size(); ++i)
    {
        delete m_devices[i].second;
    }
}

bool DeviceManager::idExists(int deviceId) const
{
    for (int i = 0; i < (int)m_devices.size(); ++i)
    {
        if (m_devices[i].first == deviceId)
        {
            return true;
        }
    }
    return false;
}

int DeviceManager::addDevice(Device *device)
{
    if (device == 0)
        return -1;

    // Benzersiz ID üret
    int newId = m_nextId;
    while (idExists(newId))
    {
        ++newId;
    }
    m_nextId = newId + 1;

    m_devices.push_back(std::make_pair(newId, device));
    return newId;
}

Device *DeviceManager::findDevice(int deviceId)
{
    for (int i = 0; i < (int)m_devices.size(); ++i)
    {
        if (m_devices[i].first == deviceId)
        {
            return m_devices[i].second;
        }
    }
    return 0;
}

bool DeviceManager::removeDevice(int deviceId)
{
    for (int i = 0; i < (int)m_devices.size(); ++i)
    {
        if (m_devices[i].first == deviceId)
        {
            delete m_devices[i].second;
            m_devices.erase(m_devices.begin() + i);
            return true;
        }
    }
    return false;
}

int DeviceManager::getDeviceCount() const
{
    return (int)m_devices.size();
}

DeviceIterator DeviceManager::createIterator()
{
    return DeviceIterator(&m_devices);
}
