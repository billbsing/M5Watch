// Page

#ifndef PAGE_H
#define PAGE_H

#include <Arduino.h>
#include <M5StickC.h>
#include <WidgetManager.h>
#include <PageManager.h>

class Page
{
public:
    Page(PageManager *manager);
    virtual void init() = 0;
    virtual void loadWidgets(WidgetManager *manager) = 0;
    virtual void draw(M5Display *lcd) = 0;
    virtual void processEvent(uint16_t eventId) = 0;

    uint8_t getIndex() const { return _index; }
    void setIndex(uint8_t value) { _index = value; }

protected:
    PageManager *getManager();
    uint16_t getNextEventId() { return _manager->getNextEventId(); }
    M5StickC* getM5() { return _manager->getM5(); }
    void selectPage(uint8_t pageId) { _manager->selectPage(pageId); }
    void pushPage(uint8_t pageId) { _manager->pushPage(pageId); }
    void popPage() { _manager->popPage(); }

private:
    PageManager *_manager;
    uint8_t _index;
};
#endif          // PAGE_H
