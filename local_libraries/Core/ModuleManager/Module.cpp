#include "Module.h"
#include "ModuleManager.h"


Module::Module(ModuleManager *manager) :
_manager(manager) {

}

void Module::raiseEvent(uint16_t eventId) {
    if ( _manager ) {
        _manager->raiseEvent(eventId);
    }
}

void Module::raiseEvent(uint16_t eventId, unsigned long delayMillis) {
    if ( _manager ) {
        _manager->raiseEvent(eventId, delayMillis);
    }
}

void Module::raiseGroupEvents(uint16_t groupId) {
    if ( _manager ) {
        _manager->raiseGroupEvents(groupId);
    }
}

void Module::removeEvent(uint16_t eventId) {
    if ( _manager ) {
        _manager->removeEvent(eventId);
    }
}

Module *Module::getModule(uint8_t id) {
    if ( _manager ) {
        return _manager->getModule(id);
    }
    return NULL;
}

/*
void Module::mountDisk() {
    if ( !SPIFFS.begin() ) {
//        logPrint("Failed to mount SPIFFS");
    }
}

void Module::unmountDisk() {
    SPIFFS.end();
}
*/

#ifdef IS_DEBUG_MODULE
void Module::debugPrint(String format, ...) {
    DebugModule *debug = (DebugModule *) getModule(DEBUG_MODULE_ID);
    if ( debug ) {
        va_list args;
        va_start (args, format);
        debug->print(_id, format, args);
        va_end (args);
    }
}
#endif

#ifdef IS_LOG_MODULE
void Module::logPrint(String format, ...) {
    LogModule *log = (LogModule *) getModule(LOG_MODULE_ID);
    if ( log ) {
        va_list args;
        va_start (args, format);
        log->print(format, args);
        va_end (args);
    }
}
#endif
