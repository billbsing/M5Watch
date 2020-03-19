// PageManager


#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include <Arduino.h>
#include <M5StickC.h>
#include <EventQueue.h>
#include "WidgetManager.h"
#include "TextWidget.h"

#define PAGE_MANGER_PAGE_LIST_SIZE              10
#define PAGE_MANAGER_NEXT_PAGE_EVENT_ID         0x00001

class Page;

class PageManager
{

public:
    PageManager(M5StickC &m5, uint16_t width, uint16_t height);
    void init();
    void add(Page *page);
    void next();
    void draw();
    void processEvent(uint16_t eventId);
    void loop();

    M5StickC& getM5() { return _m5; }
    void selectPage(String name);

    void setPosition(uint8_t index) { _position = index; }
protected:
    void loadWidgets();
    uint8_t getIndexFromName(String name);

private:
    M5StickC _m5;
    Page *_pageList[PAGE_MANGER_PAGE_LIST_SIZE];
    uint8_t _count;
    uint8_t _position;
    uint16_t _width;
    uint16_t _height;
    WidgetManager _widgetManager;
    EventQueue _eventQueue;
    TextWidget _nextPageWidget;

};

#endif          // PAGE_MANAGER_H
