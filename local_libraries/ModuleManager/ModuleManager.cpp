
#include <FS.h>

#include "ModuleManager.h"
#include "Module.h"

/*
uint16_t IgnoreDebugEventIdList[] = {
    EVENT_LED_OFF, EVENT_LED_ON,
    NULL, NULL
};
*/

ModuleManager::ModuleManager() : _length(0) {
    memset(_items, 0, sizeof(ModuleItem) * MODULES_MAX_SIZE);
}

void ModuleManager::addModule(Module *module) {
    module->setParent(this);
    if ( _length < MODULES_MAX_SIZE ) {
        _items[_length].id = module->getId();
        _items[_length].module = module;
        _length++ ;
    }
}

void ModuleManager::debugPrint(String format, ... ) {
    #ifdef IS_DEBUG_MODULE
    DebugModule *debug = (DebugModule *) getModule(DEBUG_MODULE_ID);
    if ( debug) {
        va_list args;
        va_start (args, format);
        debug->print(0, format, args);
        va_end (args);
    }
    #endif
}

void ModuleManager::init() {

    uint8_t i;
    for ( i = 0; i < _length; i ++) {
        if ( _items[i].id && _items[i].module ) {
            _items[i].module->init(this);
        }
    }

    // call all of start module start events
    debugPrint("starting modules...");
    raiseGroupEvents(EVENT_GROUP_START);
}

void ModuleManager::registerGroupEvent(uint16_t groupId, uint16_t eventId) {
    _eventGroup.assign(groupId, eventId);
}

void ModuleManager::raiseEvent(uint16_t eventId) {
    _eventQueue.push(eventId);
}

void ModuleManager::raiseGroupEvents(uint16_t groupId) {

    debugPrint("Group Event: %04X", groupId);
    uint16_t eventItems[EVENT_QUEUE_SIZE];
    uint8_t length = _eventGroup.readList(groupId, eventItems, EVENT_QUEUE_SIZE);
    unsigned long delayMillis = 0;
    if ( length > 0) {
        for ( uint8_t i = 0; i < length; i ++) {
            raiseEvent(eventItems[i], delayMillis);
            delayMillis += 100;
        }
    }
}

void ModuleManager::raiseEvent(uint16_t eventId, unsigned long delayMillis) {
    _eventQueue.push(eventId, delayMillis);
}

void ModuleManager::removeEvent(uint16_t eventId) {
    _eventQueue.remove(eventId);
}

void ModuleManager::processEvent(uint16_t eventId) {
    uint8_t i;
    for ( i = 0; i < _length; i ++) {
        if ( _items[i].id && _items[i].module ) {
            _items[i].module->processEvent(eventId);
        }
    }
}

Module *ModuleManager::getModule(uint8_t id) {
    uint8_t i;
    for ( i = 0; i < _length; i ++) {
        if ( _items[i].id && _items[i].module ) {
            if ( _items[i].id == id ) {
                return _items[i].module;
            }
        }
    }
    return NULL;
}

Module *ModuleManager::getModuleAtIndex(uint8_t index) {
    if ( index < _length) {
        return _items[index].module;
    }
    return NULL;
}

void ModuleManager::loop() {
    uint8_t i;
    for ( i = 0; i < _length; i ++) {
        if ( _items[i].id && _items[i].module ) {
            _items[i].module->loop();
        }
    }
    uint16_t eventId = _eventQueue.pop();
    if ( eventId != 0) {
        processEvent(eventId);
/*
        // only show events that are less than the log limit
        if ( !isIgnoreDebug(IgnoreDebugEventIdList, eventId) ) {
            debugPrint("Event: %04X", eventId);
        }
*/
    }
}

bool ModuleManager::isIgnoreDebug(uint16_t *eventList, uint16_t eventId) {
    uint8_t i = 0;
    while ( eventList[i] != NULL) {
        if ( eventList[i] == eventId) {
            return true;
        }
        i++;
    }
    return false;
}
