#ifndef SERIAL_DEBUG_H
#define SERIAL_DEBUG_H

#define DEBUG_LOG_ITEM_SIZE        80

#include <Arduino.h>
typedef struct {
    bool isUsed;
    String message;
} DebugItem;


class SerialDebug {

public:
    void begin(uint16_t baudRate);
    void print(String format, ... );
    void print(String format, va_list args);

protected:
    void addMessage(String message);

private:
    DebugItem _logItems[DEBUG_LOG_ITEM_SIZE];
    bool _isSerial;

};


#endif				// SERIAL_DEBUG_H
