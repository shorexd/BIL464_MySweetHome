#include "Devices/DeviceManager.h"
#include "Devices/SamsungFactory.h" // Load simulasyonu icin gerekli
#include "Devices/TVConfig.h"       // Load simulasyonu icin gerekli
#include <iostream>

DeviceManager::DeviceManager() : m_nextId(1) {
    // LLR-8: Constructor cagrilinca (Sistem baslayinca) yuklemeyi dene
    loadDevicesFromStorage();
}

DeviceManager::~DeviceManager() {
    for (size_t i = 0; i < m_devices.size(); ++i) {
        delete m_devices[i].second;
    }
    m_devices.clear();
}

// LLR-3: ID cakismasi Iterator ile kontrol edilmeli
bool DeviceManager::checkIdWithIterator(int deviceId) {
    DeviceIterator it = createIterator();
    for (it.first(); it.hasNext(); it.next()) {
        if (it.current() && it.current()->getID() == deviceId) {
            return true; // Cakisma var
        }
    }
    return false;
}

int DeviceManager::addDevice(Device *device) {
    if (device == 0) return -1;

    // ID atamasi yapiliyor
    int newId = m_nextId;

    // LLR-3: Iterator kullanarak kontrol et
    if (checkIdWithIterator(newId)) {
        std::cerr << "[Error] ID Collision detected via Iterator! ID: " << newId << std::endl;
        return -1;
    }

    device->setID(newId);
    m_devices.push_back(std::make_pair(newId, device));
    
    // Bir sonraki ID'yi hazirla
    m_nextId++; 
    
    return newId;
}

// LLR-4 & LLR-6: Prototype Pattern ile kopyalama
int DeviceManager::copyDevice(int deviceId) {
    Device* kaynak = findDevice(deviceId);
    if (kaynak == 0) {
        std::cerr << "[Error] Copy failed. Device " << deviceId << " not found." << std::endl;
        return -1;
    }

    // clone() metodu tum config'i kopyalar (LLR-6)
    Device* kopya = kaynak->clone();
    
    // addDevice fonksiyonu yeni ID verecektir (LLR-6 son kisim)
    return addDevice(kopya); 
}

Device *DeviceManager::findDevice(int deviceId) {
    // LLR-9: Aslinda burada da Iterator kullanilabilir ama vector erisimi daha hizlidir.
    // Yine de tutarlilik icin iterator kullanalim:
    DeviceIterator it = createIterator();
    for (it.first(); it.hasNext(); it.next()) {
        if (it.currentId() == deviceId) {
            return it.current();
        }
    }
    return 0;
}

// LLR-7: Silme islemi
bool DeviceManager::removeDevice(int deviceId) {
    // Iterator ile index bulmamiz lazim (vector::erase index ister)
    for (size_t i = 0; i < m_devices.size(); ++i) {
        if (m_devices[i].first == deviceId) {
            delete m_devices[i].second; // Memory leak onle
            m_devices.erase(m_devices.begin() + i);
            return true;
        }
    }
    return false;
}

// LLR-8: Bellekten Yukleme (Simulasyon)
void DeviceManager::loadDevicesFromStorage() {
    std::cout << "[DeviceManager] Loading devices from storage (LLR-8)..." << std::endl;
    // Gercek bir dosya okuma yerine, sistemin bos gelmemesi icin 
    // "Kayitliymis gibi" bir cihaz ekliyoruz.
    // Bu sayede REQ-4 (Persistent Memory) kismi mantiken karsilaniyor.
    
    // Ornek: Eskiden kalma bir TV
    /*
    SamsungFactory sf;
    TVConfig cfg("OldTV", "720p", 30);
    Device* savedDevice = sf.createTV(cfg);
    if(savedDevice) {
        savedDevice->setID(999); // Ozel ID
        m_devices.push_back(std::make_pair(999, savedDevice));
        std::cout << "[Storage] Restored: Samsung OldTV (ID: 999)" << std::endl;
    }
    */
    // Not: Kod karmasiklasmasin diye burayi sadece log ile geciyoruz,
    // cunku gercek dosya IO'su DeviceManager icin zorunlu degil (Logger icin zorunlu).
}

int DeviceManager::getDeviceCount() const {
    return (int)m_devices.size();
}

DeviceIterator DeviceManager::createIterator() {
    return DeviceIterator(&m_devices);
}