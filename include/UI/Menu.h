#ifndef MENU_H
#define MENU_H

#include "MenuParts.h" // Yeni parcalar
#include <vector>
#include <string>

class Menu {
private:
    std::string title;
    // LLR-01: vector<MenuEntry> yapisi
    std::vector<MenuEntry> entries;
    
    // Composition: Helper siniflar
    MenuRenderer renderer;
    KeyboardInputHandler inputHandler;

public:
    Menu(const std::string& menuTitle);
    ~Menu();

    void addCommand(char key, Command* cmd); // Key parametresi eklendi
    void run();
};

#endif