#ifndef DEVICE_ITERATOR_H
#define DEVICE_ITERATOR_H

#include <vector>
#include <utility>
#include "../murat-devices/Device.h" // Murat'ın Device.h dosyası

class DeviceIterator
{
public:
    // ID + Device* birlikte tutulacak
    DeviceIterator(std::vector<std::pair<int, Device *>> *records);

    void first();         // listenin başına git
    void next();          // bir sonrakine geç
    bool hasNext() const; // devam edecek eleman var mı?

    Device *current() const; // şu anki cihaz
    int currentId() const;   // şu anki cihazın ID'si

private:
    std::vector<std::pair<int, Device *>> *m_records;
    int m_index;
};

#endif
