#ifndef FILELOGTARGET_H
#define FILELOGTARGET_H

#include "ILogTarget.h"
#include <fstream>
#include <iostream>

class FileLogTarget : public ILogTarget {
private:
    std::ofstream m_file;
public:
    FileLogTarget(const std::string& filename) {
        m_file.open(filename.c_str(), std::ios::app); // Ekleme modu (LLR-05)
        if (!m_file.is_open()) {
            std::cerr << "[FileLogTarget] ERROR: Dosya acilamadi: " << filename << std::endl;
        }
    }

    ~FileLogTarget() {
        if (m_file.is_open()) {
            m_file.close();
        }
    }

    void write(const std::string& formattedMessage) {
        if (m_file.is_open()) {
            m_file << formattedMessage << std::endl;
            m_file.flush(); // LLR-06: Veri kaybi olmasin diye flush
        }
    }
};

#endif