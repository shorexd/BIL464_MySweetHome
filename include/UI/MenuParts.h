#ifndef MENUPARTS_H
#define MENUPARTS_H

#include "Command.h"
#include <string>
#include <vector>

// LLR-03: MenuEntry yapisi
struct MenuEntry {
    char key;           
    std::string label;  
    Command* action;    

    // Sadece bildirim (Implementation .cpp dosyasinda)
    MenuEntry(char k, const std::string& l, Command* c);
};

// LLR-07: MenuRenderer sinifi
class MenuRenderer {
public:
    void render(const std::string& title, const std::vector<MenuEntry>& entries);
};

// LLR-10: KeyboardInputHandler sinifi
class KeyboardInputHandler {
public:
    char getKey();
    int getInt();
};

#endif