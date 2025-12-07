#include "DeviceIterator.h"

DeviceIterator::DeviceIterator(std::vector<std::pair<int, Device *>> *records)
    : m_records(records), m_index(0) {}

void DeviceIterator::first()
{
    m_index = 0;
}

bool DeviceIterator::hasNext() const
{
    if (m_records == 0)
        return false;
    return m_index < (int)m_records->size();
}

void DeviceIterator::next()
{
    if (hasNext())
    {
        ++m_index;
    }
}

Device *DeviceIterator::current() const
{
    if (!hasNext())
        return 0;
    return (*m_records)[m_index].second;
}

int DeviceIterator::currentId() const
{
    if (!hasNext())
        return -1;
    return (*m_records)[m_index].first;
}
