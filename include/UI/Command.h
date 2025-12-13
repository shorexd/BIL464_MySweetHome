#ifndef COMMAND_H
#define COMMAND_H

// Command Arayuzu
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual const char* getDescription() const = 0; // Menude ne yazacagini dondurur
};

#endif