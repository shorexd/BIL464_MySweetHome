#include "UI/Menu.h"
#include <iostream>
#include <limits>

Menu::Menu(const std::string& menuTitle) : title(menuTitle) {}

Menu::~Menu() {
    // Menu yok olurken komutlari temizle (Memory Leak onlemi)
    for (size_t i = 0; i < commands.size(); ++i) {
        delete commands[i];
    }
    commands.clear();
}

void Menu::addCommand(Command* cmd) {
    commands.push_back(cmd);
}

void Menu::run() {
    bool running = true;
    while (running) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "   " << title << std::endl;
        std::cout << "========================================" << std::endl;

        // Secenekleri Listele
        for (size_t i = 0; i < commands.size(); ++i) {
            std::cout << "[" << (i + 1) << "] " << commands[i]->getDescription() << std::endl;
        }
        std::cout << "[0] Cikis / Geri" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Komut > ";

        int choice;
        if (!(std::cin >> choice)) {
            // Hatali giris (harf vs.) temizligi
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << ">> Hata: Gecersiz giris! Tekrar deneyin." << std::endl;
            continue;
        }

        if (choice == 0) {
            running = false;
            std::cout << ">> Menuden cikiliyor..." << std::endl;
        } 
        else if (choice > 0 && choice <= (int)commands.size()) {
            // Komutu calistir
            std::cout << "\n>> Islem Baslatiliyor..." << std::endl;
            commands[choice - 1]->execute();
        } 
        else {
            std::cout << ">> Hata: Gecersiz secenek!" << std::endl;
        }
    }
}