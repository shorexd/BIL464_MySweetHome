// src/Logger.cpp
#include "Logger.h"
#include <iostream>
#include <ctime>

namespace {
    // Zaman damgası üretmek için yardımcı fonksiyon (C++98 uyumlu)
    std::string currentDateTime() {
        std::time_t now = std::time(0);  // C++98'de 0 kullanılır
        char buf[32];
        if (std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S",
                          std::localtime(&now))) {
            return std::string(buf);
        }
        return std::string();
    }
}

Logger& Logger::getInstance() {
    // Fonksiyon scope static'i C++98'de destekleniyor
    static Logger instance;
    return instance;
}

Logger::Logger() : m_file() {
}

Logger::~Logger() {
    close();
}

void Logger::open(const std::string& filename) {
    if (!m_file.is_open()) {
        m_file.open(filename.c_str());
        if (!m_file) {
            std::cerr << "[Logger] ERROR: Could not open log file: "
                      << filename << std::endl;
        }
    }
}

void Logger::close() {
    if (m_file.is_open()) {
        m_file.flush();
        m_file.close();
    }
}

bool Logger::isOpen() const {
    return m_file.is_open();
}

void Logger::log(const std::string& message) {
    std::string line = "[" + currentDateTime() + "] " + message;

    if (m_file.is_open()) {
        m_file << line << std::endl;
    }

    // Ekrana da bas
    std::cout << line << std::endl;
}

void Logger::logError(const std::string& message) {
    log(std::string("ERROR: ") + message);
}
