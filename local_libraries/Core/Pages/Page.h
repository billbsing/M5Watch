// Page

#ifndef PAGE_H
#define PAGE_H

#include "../core.h"
#include "../Widgets/WidgetManager.h"
#include "PageManager.h"

class Page
{
public:
    Page();
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
    uint16_t getHeaderHeight() const;

    void setManager(PageManager *value) { _manager = value; }
    PageManager *getManager() const { return _manager; }

protected:
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
