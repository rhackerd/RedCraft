#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "logging.hpp"

class Settings {
public:
    Settings();
    ~Settings();
    void Draw();

private:
    int volume;
    int resolution;
    
};


#endif