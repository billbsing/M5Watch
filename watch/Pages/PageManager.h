// PageManager


#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include <Arduino.h>
#include <M5StickC.h>
#include <EventQueue.h>
#include "WidgetManager.h"

#define PAGE_MANGER_PAGE_LIST_SIZE       10

class Page;

class PageManager
{

public:
    PageManager(uint16_t width, uint16_t height);
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

};

#endif          // PAGE_MANAGER_H
