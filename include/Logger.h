// include/Logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
public:
    // Singleton erişim noktası
    static Logger& getInstance();

    // Log dosyasını aç (varsayılan isim: msh_log.txt)
    void open(const std::string& filename = "msh_log.txt");

    // Log dosyasını kapat
    void close();

    // Dosya açık mı?
    bool isOpen() const;

    // Genel log fonksiyonu
    void log(const std::string& message);

    // Hata loglamak için kısayol
    void logError(const std::string& message);

private:
    Logger();
    ~Logger();

    // Kopyalama yasak (Singleton)
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::ofstream m_file;
};

#endif // LOGGER_H
