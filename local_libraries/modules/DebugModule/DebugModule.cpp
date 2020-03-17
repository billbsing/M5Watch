#include "DebugModule.h"


DebugModule::DebugModule(uint8_t id, String name, uint16_t serialBaud):
Module(id, name) {
    _isSerial = false;
    if ( serialBaud > 0) {
        Serial.begin(serialBaud);
        while(!Serial) { }
        Serial.println();
        _isSerial = true;
    }
//    memset(_logItems, 0, sizeof(DebugItem) * DEBUG_LOG_ITEM_SIZE);
    for ( uint8_t i = 0; i < DEBUG_LOG_ITEM_SIZE; i ++) {
        _logItems[i].isUsed= false;
    }
}

void DebugModule::init(ModuleManager *manager) {
    debugPrint("Debug started");
}

void DebugModule::processEvent(uint16_t eventId) {
}

void DebugModule::print(uint8_t moduleId, String format, ... ) {
    va_list args;
    va_start (args, format);
    print(moduleId, format, args);
    va_end (args);
}

void DebugModule::print(uint8_t moduleId, String format, va_list args) {
    char buffer[1024];
    char moduleText[8];
    sprintf(moduleText, "%02X: ", moduleId);
    String newFormat = String(moduleText + format);
    vsnprintf (buffer, 1023, newFormat.c_str(), args);
    if ( _isSerial ){
        Serial.println(buffer);
    }
    addMessage(moduleId, buffer);
}

void DebugModule::addMessage(uint8_t moduleId, String message) {
    uint16_t i;
    for (i = DEBUG_LOG_ITEM_SIZE - 2; i > 0;  --i ) {
        _logItems[i].isUsed = _logItems[i - 1].isUsed;
        _logItems[i].message = _logItems[i - 1].message;
    }
    _logItems[0].isUsed = true;
    _logItems[0].message = message;
}
