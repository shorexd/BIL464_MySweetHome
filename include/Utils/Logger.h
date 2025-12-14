#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>
#include "ILogTarget.h"

// LLR-03: Log Seviyeleri
enum LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    static Logger& getInstance();

    // Hedef Yonetimi (LLR-04)
    void attachTarget(ILogTarget* target);
    
    // Loglama Fonksiyonlari
    void log(LogLevel level, const std::string& message);
    
    // Mevcut kodlarla uyumluluk icin (Varsayilan INFO)
    void log(const std::string& message);

private:
    Logger();
    ~Logger();
    
    // Kopyalama Yasak
    Logger(const Logger&);
    Logger& operator=(const Logger&);

    std::vector<ILogTarget*> targets;
    
    // Yardimci: Zaman damgasi (C++98)
    std::string getCurrentTime();
    std::string getLevelString(LogLevel level);
};

#endif