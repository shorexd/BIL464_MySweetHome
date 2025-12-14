#ifndef TVCONFIG_H
#define TVCONFIG_H

#include <string>

struct TVConfig {
    std::string model;
    std::string resolution; // "4K", "1080p" etc.
    int fps;                // 60, 120 etc.

    TVConfig(const std::string& m, const std::string& r, int f)
        : model(m), resolution(r), fps(f) {}
};

#endif