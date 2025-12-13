#ifndef MENU_H
#define MENU_H

#include "Command.h"
#include <vector>
#include <string>

class Menu {
private:
    std::string title;
    std::vector<Command*> commands;

public:
    Menu(const std::string& menuTitle);
    ~Menu();

    void addCommand(Command* cmd);
    void run(); // Ana dongu burada doner
};

#endif