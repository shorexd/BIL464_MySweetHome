#ifndef ILOGTARGET_H
#define ILOGTARGET_H

#include <string>

class ILogTarget {
public:
    virtual ~ILogTarget() {}
    // Saf sanal fonksiyon: Her hedef bunu kendine gore dolduracak
    virtual void write(const std::string& formattedMessage) = 0;
};

#endif