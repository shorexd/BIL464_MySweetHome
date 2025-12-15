#ifndef GENERALCOMMANDS_H
#define GENERALCOMMANDS_H

#include "Command.h"
#include <string>

// Forward Declaration (Dairesel bagimliligi onlemek icin)
class SystemController;

// Helper fonksiyon tanimi
void listDevices(SystemController* sys, int filterMode = 0);
std::string intToString(int val);

// --- SINIF TANIMLARI ---

class AddDeviceCommand : public Command {
public:
    void execute();
    const char* getDescription() const;
};

class RemoveDeviceCommand : public Command {
public:
    void execute();
    const char* getDescription() const;
};

class PowerControlCommand : public Command {
    bool on;
public:
    PowerControlCommand(bool o);
    void execute();
    const char* getDescription() const;
};

class SetModeCommand : public Command {
public:
    void execute();
    const char* getDescription() const;
};

class SetStateCommand : public Command {
public:
    void execute();
    const char* getDescription() const;
};

class ManualCommand : public Command {
public:
    void execute();
    const char* getDescription() const;
};

class AboutCommand : public Command {
public:
    void execute();
    const char* getDescription() const;
};

class ReportCommand : public Command {
public:
    void execute();
    const char* getDescription() const;
};

class SimulationCommand : public Command {
public:
    void execute();
    const char* getDescription() const;
};

#endif