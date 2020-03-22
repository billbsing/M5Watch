#ifndef MODULE_H
#define MODULE_H

#include "ModuleManager.h"
#include <FS.h>

class ModuleManager;

class Module
{

public:

    Module(ModuleManager *manager);

    virtual void init() = 0;
    virtual void processEvent(uint16_t eventId) = 0;
    virtual void loop() = 0;

    ModuleManager *getManager() { return _manager; }

    #ifdef IS_DEBUG_MODULE
    void debugPrint(String format, ...);
    #endif

    #ifdef IS_LOG_MODULE
    void logPrint(String format, ...);
    #endif

protected:
    void raiseEvent(uint16_t eventId);
    void raiseEvent(uint16_t eventId, unsigned long delayMillis);
    void raiseGroupEvents(uint16_t groupId);
    void removeEvent(uint16_t eventId);
    Module *getModule(uint8_t id);
    // void mountDisk();
    // void unmountDisk();

private:
    ModuleManager *_manager;
};

#endif      // MODULE_H
