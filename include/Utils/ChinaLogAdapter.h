#ifndef CHINALOGADAPTER_H
#define CHINALOGADAPTER_H

#include "ILogTarget.h"
#include <iostream>

// LLR-10: Cin mali cihaz uyumlulugu
class ChinaLogAdapter : public ILogTarget {
public:
    // "Cin Cihazi API" simulasyonu (LLR-10'daki sendLog)
    void sendLogToChinaDevice(const char* data, int length) {
        // Burada gercek donanim surucusu cagirilir.
        // Biz simulasyon yapiyoruz:
        std::cout << "[ChinaDevice Hardware] Sending " << length << " bytes: " << data << std::endl;
    }

    // Adapter Arayuzu
    void write(const std::string& formattedMessage) {
        // Baglanti hatasi simulasyonu (LLR-10)
        bool connectionActive = true; 
        
        if (connectionActive) {
            // String'i char*'a cevirip API'ye gonderiyoruz
            sendLogToChinaDevice(formattedMessage.c_str(), formattedMessage.length());
        } else {
            std::cerr << "[ChinaAdapter] WARNING: Cihaza erisilemedi!" << std::endl;
        }
    }
};

#endif