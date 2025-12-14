#ifndef MENUPARTS_H
#define MENUPARTS_H

#include "Command.h"
#include <string>
#include <iostream>
#include <vector>
#include <limits>

// LLR-03: MenuEntry yapisi
struct MenuEntry {
    char key;           // Menude secim tusu (1, 2, a, b...)
    std::string label;  // Ekranda gorunecek yazi
    Command* action;    // Calisacak komut

    MenuEntry(char k, const std::string& l, Command* c) 
        : key(k), label(l), action(c) {}
};

// LLR-07: MenuRenderer sinifi
class MenuRenderer {
public:
    void render(const std::string& title, const std::vector<MenuEntry>& entries) {
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
};

// LLR-10: KeyboardInputHandler sinifi
class KeyboardInputHandler {
public:
    char getKey() {
        char choice;
        if (std::cin >> choice) {
            return choice;
        } else {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return '\0'; // Gecersiz
        }
    }
    
    // Sayisal girisler icin yardimci
    int getInt() {
        int val;
        if (std::cin >> val) return val;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return -1;
    }
};

#endif