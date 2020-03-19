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
    PageManager(uint16_t width, uint16_t height);
    void init();
    void add(Page *page);
    void next();
    void show(M5Display &lcd);
    void loop(M5StickC &m5);

protected:
    void loadWidgets();

private:
    M5Display *_lcd;
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
