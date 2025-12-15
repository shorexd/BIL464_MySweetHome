#include "UI/MenuParts.h"
#include <iostream>
#include <limits>

// MenuEntry Constructor
MenuEntry::MenuEntry(char k, const std::string& l, Command* c) 
    : key(k), label(l), action(c) {}

// MenuRenderer Implementasyonu
void MenuRenderer::render(const std::string& title, const std::vector<MenuEntry>& entries) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "   " << title << std::endl;
    std::cout << "========================================" << std::endl;

    for (size_t i = 0; i < entries.size(); ++i) {
        std::cout << "[" << entries[i].key << "] " << entries[i].label << std::endl;
    }
    std::cout << "[0] Cikis / Geri" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Komut > ";
}

// KeyboardInputHandler Implementasyonu
char KeyboardInputHandler::getKey() {
    char choice;
    if (std::cin >> choice) {
        return choice;
    } else {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return '\0'; 
    }
}

int KeyboardInputHandler::getInt() {
    int val;
    if (std::cin >> val) return val;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    return -1;
}