#ifndef DEBUG_MODULE_H
#define DEBUG_MODULE_H

#include "ModuleManager.h"
#include "Module.h"

#define DEBUG_LOG_ITEM_SIZE        80

typedef struct {
    bool isUsed;
    String message;
} DebugItem;


class DebugModule : public Module {

public:
    DebugModule(uint8_t id, String name, uint16_t serialBaud);
    void init(ModuleManager *manager);
    void processEvent(uint16_t eventId);
    void loop() {};
    void print(uint8_t moduleId, String format, ... );
    void print(uint8_t moduleId, String format, va_list args);

protected:
    void addMessage(uint8_t moduleId, String message);

private:
    DebugItem _logItems[DEBUG_LOG_ITEM_SIZE];
    bool _isSerial;

};


#endif				// DEBUG_MODULE_H
