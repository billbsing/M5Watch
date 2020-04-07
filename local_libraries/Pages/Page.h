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
    virtual void begin() = 0;
    virtual void end() = 0;
    virtual void loadWidgets(WidgetManager *manager) = 0;
    virtual void draw(M5Display *lcd) = 0;
    virtual void processEvent(uint16_t eventId) = 0;

    uint8_t getIndex() const { return _index; }
    void setIndex(uint8_t value) { _index = value; }
    bool isVisible() { return _isVisible; }
    void setVisible(bool value) { _isVisible = value; }

protected:
    PageManager *getManager();
    uint16_t getNextEventId() { return _manager->getNextEventId(); }
    M5StickC* getM5() { return _manager->getM5(); }
    M5Display* getLcd() { return _manager->getLcd(); }
    void selectPage(uint8_t pageId) { _manager->selectPage(pageId); }
    void pushPage(uint8_t pageId) { _manager->pushPage(pageId); }
    void popPage() { _manager->popPage(); }
    void drawPage();
    void drawHeader(M5Display *lcd, String title);


private:
    PageManager *_manager;
    uint8_t _index;
    bool _isVisible;
};
#endif          // PAGE_H
