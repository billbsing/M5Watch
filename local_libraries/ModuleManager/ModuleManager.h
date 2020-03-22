#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include <arduino.h>
// #include "Module.h"
#include "EventQueue.h"
#include "EventGroup.h"

#define MODULES_MAX_SIZE        40

#define EVENT_GROUP_START       0x0001

class Module;
// class EventGroup;
// class EventQueue;

typedef struct {
    uint8_t id;
    Module *module;
} ModuleItem;

class ModuleManager
{
public:
    ModuleManager();
    void add(uint8_t moduleId, Module *module);
    void init();
    void raiseEvent(uint16_t eventId);
    void raiseEvent(uint16_t eventId, uint32_t delayMillis);
    void raiseGroupEvents(uint16_t groupId);
    void removeEvent(uint16_t eventId);
    void processEvent(uint16_t eventId);
    Module *getModule(uint8_t id);
    Module *getModuleAtIndex(uint8_t index);
    void readData(String filename);
    size_t writeData(String filename);

    void loop();
    
    #ifdef IS_DEBUG_MODULE
    void debugPrint(String format, ... );
    #endif

    uint8_t getModuleCount() { return _length; }
    void registerGroupEvent(uint16_t groupId, uint16_t eventId);

    uint8_t getQueueMax() { return _eventQueue.getMaxCount(); }
    uint8_t getGroupCount() { return _eventGroup.getCount(); }

protected:
    bool isIgnoreDebug(uint16_t *eventList, uint16_t eventId);

private:
    ModuleItem _items[MODULES_MAX_SIZE];
    uint8_t _length;
    EventQueue _eventQueue;
    EventGroup _eventGroup;

};

#endif      // MODULE_MANAGER_H
