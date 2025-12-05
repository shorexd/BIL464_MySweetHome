// src/Logger.cpp
#include "Logger.h"
#include <iostream>
#include <ctime>

namespace {
    // Zaman damgası üretmek için yardımcı fonksiyon
    std::string currentDateTime() {
        std::time_t now = std::time(nullptr);
        char buf[32]{};
        if (std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S",
                          std::localtime(&now))) {
            return std::string(buf);
        }
        return {};
    }
}

Logger::Logger() {}

Logger::~Logger() {
    close(); // Program biterken dosyayı kapat
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::open(const std::string& filename) {
    if (m_file.is_open()) {
        return; // Zaten açık
    }

    m_file.open(filename.c_str(), std::ios::out | std::ios::app);
    if (!m_file) {
        std::cerr << "Logger: Could not open log file: " << filename << "\n";
        return;
    }

    m_file << "==============================\n";
    m_file << "[" << currentDateTime() << "] MSH started\n";
    m_file.flush();
}

void Logger::close() {
    if (m_file.is_open()) {
        m_file << "[" << currentDateTime() << "] MSH shutting down\n";
        m_file << "==============================\n\n";
        m_file.flush();
        m_file.close();
    }
}

bool Logger::isOpen() const {
    return m_file.is_open();
}

void Logger::log(const std::string& message) {
    if (!m_file.is_open()) {
        // Kimse open() çağırmadıysa, varsayılan isimle aç
        open();
    }

    if (m_file.is_open()) {
        m_file << "[" << currentDateTime() << "] " << message << "\n";
        m_file.flush();
    }
}

void Logger::logError(const std::string& message) {
    log("ERROR: " + message);
}
