#include "Utils/Logger.h"
#include <iostream>
#include <ctime>
#include <sstream>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() {}

Logger::~Logger() {
    // LLR-06: Shutdown sirasinda hedefleri temizle
    for (size_t i = 0; i < targets.size(); ++i) {
        delete targets[i];
    }
    targets.clear();
}

void Logger::attachTarget(ILogTarget* target) {
    targets.push_back(target);
}

std::string Logger::getLevelString(LogLevel level) {
    switch(level) {
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

std::string Logger::getCurrentTime() {
    std::time_t now = std::time(0);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

void Logger::log(LogLevel level, const std::string& message) {
    // LLR-03: Formatlama (Zaman + Seviye + Mesaj)
    std::stringstream ss;
    ss << "[" << getCurrentTime() << "] [" << getLevelString(level) << "] " << message;
    std::string formattedMsg = ss.str();

    // LLR-04: Tum hedeflere dagit (Loop)
    for (size_t i = 0; i < targets.size(); ++i) {
        if (targets[i]) {
            targets[i]->write(formattedMsg);
        }
    }
    
    // Konsola da basalim ki gorelim
    // std::cout << formattedMsg << std::endl; 
    // (Not: FileLogTarget ve ChinaAdapter zaten ekrana bilgi veriyor, burayi kapattim dublike olmasin)
}

// Uyumluluk modu
void Logger::log(const std::string& message) {
    log(INFO, message);
}