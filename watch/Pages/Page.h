// Page

#ifndef PAGE_H
#define PAGE_H

#include <Arduino.h>
#include <M5StickC.h>
#include "WidgetManager.h"
#include "PageManager.h"

class Page
{
public:
    Page(String name, PageManager &manager);
    virtual void init() = 0;
    virtual void loadWidgets(WidgetManager *manager) = 0;
    virtual void draw(M5Display &lcd) = 0;
    virtual void processEvent(uint16_t eventId) = 0;

    uint8_t getIndex() const { return _index; }
    void setIndex(uint8_t value) { _index = value; }

    String getName() const { return _name; }
    
protected:
    PageManager &getManager();
    uint16_t getNextEventId();
    M5StickC& getM5() { return _manager.getM5(); }
    void selectPage(String name) { _manager.selectPage(name); }

private:
    PageManager _manager;
    String _name;
    uint8_t _index;
    uint8_t _eventIndex;
};
#endif          // PAGE_H
