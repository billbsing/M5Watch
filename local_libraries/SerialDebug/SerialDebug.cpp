#include "SerialDebug.h"


void SerialDebug::begin(uint16_t baudRate) {
    _isSerial = false;
    if ( baudRate > 0) {
        Serial.begin(baudRate);
        while(!Serial) { }
        Serial.println();
        _isSerial = true;
    }
    for ( uint8_t i = 0; i < DEBUG_LOG_ITEM_SIZE; i ++) {
        _logItems[i].isUsed= false;
    }
}

void SerialDebug::print(String format, ... ) {
    va_list args;
    va_start (args, format);
    print(format, args);
    va_end (args);
}

void SerialDebug::print(String format, va_list args) {
    char buffer[1024];
    char moduleText[8];
    String newFormat = String(format);
    vsnprintf (buffer, 1023, newFormat.c_str(), args);
    if ( _isSerial ){
        Serial.println(buffer);
    }
    addMessage(buffer);
}

void SerialDebug::addMessage(String message) {
    uint16_t i;
    for (i = DEBUG_LOG_ITEM_SIZE - 2; i > 0;  --i ) {
        _logItems[i].isUsed = _logItems[i - 1].isUsed;
        _logItems[i].message = _logItems[i - 1].message;
    }
    _logItems[0].isUsed = true;
    _logItems[0].message = message;
}
