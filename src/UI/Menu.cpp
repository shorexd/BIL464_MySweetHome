#include "UI/Menu.h"
#include <iostream>

Menu::Menu(const std::string& menuTitle) : title(menuTitle) {}

Menu::~Menu() {
    for (size_t i = 0; i < entries.size(); ++i) {
        delete entries[i].action;
    }
    entries.clear();
}

void Menu::addCommand(char key, Command* cmd) {
    // Command icindeki description'i alip MenuEntry olusturuyoruz
    entries.push_back(MenuEntry(key, cmd->getDescription(), cmd));
}

void Menu::run() {
    bool running = true;
    while (running) {
        // LLR-07: Renderer kullanimi
        renderer.render(title, entries);

        // LLR-10: InputHandler kullanimi
        char choice = inputHandler.getKey();

        if (choice == '0') {
            running = false;
            std::cout << ">> Menuden cikiliyor..." << std::endl;
        } else {
            bool found = false;
            // LLR-06: Komutu bul ve calistir
            for (size_t i = 0; i < entries.size(); ++i) {
                if (entries[i].key == choice) {
                    std::cout << "\n>> Islem Baslatiliyor..." << std::endl;
                    entries[i].action->execute();
                    found = true;
                    break;
                }
            }
            if (!found) { // LLR-11: Gecersiz tus
                std::cout << ">> Hata: Gecersiz secenek!" << std::endl;
            }
        }
    }
}