#ifndef MODULE_H
#define MODULE_H

#include "ModuleManager.h"
#include <FS.h>

class ModuleManager;
class WebServerModule;

class Module
{

public:

    Module(uint8_t id, String name);

    virtual void init(ModuleManager *manager) = 0;
    virtual void processEvent(uint16_t eventId) = 0;
    virtual void loop() = 0;
//    virtual String webServerHook(uint8_t hookId, WebServerModule *webServer) = 0;

    void setParent(ModuleManager *manager) { _manager = manager; }
    ModuleManager *getParent() { return _manager; }
    uint8_t getId() { return _id; }
    String getName() { return _name; }
    void debugPrint(String format, ...);
    void logPrint(String format, ...);

protected:
    void raiseEvent(uint16_t eventId);
    void raiseEvent(uint16_t eventId, unsigned long delayMillis);
    void raiseGroupEvents(uint16_t groupId);
    void removeEvent(uint16_t eventId);
    Module *getModule(uint8_t id);
    // void mountDisk();
    // void unmountDisk();

private:
    uint8_t _id;
    ModuleManager *_manager;
    String _name;
};

#endif      // MODULE_H
