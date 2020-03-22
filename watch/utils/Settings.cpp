#include "Settings.h"

Settings::Settings(String name):
_name(name),
_isOpen(false),
_isBlockOpen(false) {

}

void Settings::begin(bool isReadOnly) {
    open(isReadOnly);
}

void Settings::end() {
    close();
}

bool Settings::open(bool isReadOnly) {
    bool isNeedToClose = false;
    if ( ! _isOpen ) {
        _preferences.begin(_name.c_str(), false);
        _isOpen = true;
        isNeedToClose = true;
    }
    return isNeedToClose;
}

void Settings::close() {
    if ( _isOpen ) {
        _preferences.end();
        _isOpen = false;
    }
}

void Settings::blockOpen(bool isReadOnly) {
    _isBlockOpen = open(isReadOnly);
}

void Settings::blockClose() {
    if ( _isBlockOpen ) {
        close();
        _isBlockOpen = false;
    }
}

uint32_t Settings::getAutoPowerOffTimeout() {
    uint32_t value;
    blockOpen(true);
    value = _preferences.getULong("autoPowerOffTimeout", AUTO_POWER_OFF_MILLIS);
    blockClose();
    return value;
}
