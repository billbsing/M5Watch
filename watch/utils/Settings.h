/*

Settings

*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <Preferences.h>


#define AUTO_POWER_OFF_MILLIS       ( 1000 * 30 )

class Settings {
public:
    Settings(String name);
    void begin(bool isReadOnly);
    void end();
    bool open(bool isReadOnly);
    void close();
    void blockOpen(bool isReadOnly);
    void blockClose();
    uint32_t getAutoPowerOffTimeout();

private:
    bool _isOpen;
    bool _isBlockOpen;
    String _name;
    Preferences _preferences;
};



#endif              // SETTINGS_H
