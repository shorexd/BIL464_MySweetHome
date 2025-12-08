#include "Devices/DeviceManager.h" // Duzeltildi
#include <iostream> // Hata mesaji icin

DeviceManager::DeviceManager() : m_nextId(1) {}

DeviceManager::~DeviceManager() {
    for (size_t i = 0; i < m_devices.size(); ++i) {
        delete m_devices[i].second;
    }
    m_devices.clear();
}

bool DeviceManager::idExists(int deviceId) const {
    for (size_t i = 0; i < m_devices.size(); ++i) {
        if (m_devices[i].first == deviceId) return true;
    }
    return false;
}

int DeviceManager::addDevice(Device *device) {
    if (device == 0) return -1;

    int newId = m_nextId++;
    // Murat'in Device sinifina da ID'yi isleyelim (Onemli!)
    device->setID(newId);

    m_devices.push_back(std::make_pair(newId, device));
    return newId;
}

// --- PROTOTYPE UYGULAMASI (Kritik) ---
int DeviceManager::copyDevice(int deviceId) {
    Device* kaynak = findDevice(deviceId);
    if (kaynak == 0) {
        std::cerr << "[Error] Copy failed. Device " << deviceId << " not found." << std::endl;
        return -1;
    }

    // Klonla (Prototype Pattern)
    Device* kopya = kaynak->clone();
    
    // Yeni ID ver ve kaydet
    return addDevice(kopya);
}

Device *DeviceManager::findDevice(int deviceId) {
    for (size_t i = 0; i < m_devices.size(); ++i) {
        if (m_devices[i].first == deviceId) return m_devices[i].second;
    }
    return 0;
}

bool DeviceManager::removeDevice(int deviceId) {
    for (size_t i = 0; i < m_devices.size(); ++i) {
        if (m_devices[i].first == deviceId) {
            delete m_devices[i].second;
            m_devices.erase(m_devices.begin() + i);
            return true;
        }
    }
    return false;
}

int DeviceManager::getDeviceCount() const {
    return (int)m_devices.size();
}

DeviceIterator DeviceManager::createIterator() {
    return DeviceIterator(&m_devices);
}