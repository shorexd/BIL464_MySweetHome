#ifndef DEVICE_ITERATOR_H
#define DEVICE_ITERATOR_H

#include <vector>
#include <utility>
#include "Device.h" 

class DeviceIterator {
public:
    // DIKKAT: > > arasinda bosluk var (C++98 kurali)
    DeviceIterator(std::vector<std::pair<int, Device *> > *records);

    void first();
    void next();
    bool hasNext() const;
    Device *current() const;
    int currentId() const;

private:
    // DIKKAT: > > arasinda bosluk var
    std::vector<std::pair<int, Device *> > *m_records;
    int m_index;
};

#endif