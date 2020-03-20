// PageManager


#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include <Arduino.h>
#include <M5StickC.h>
#include <EventQueue.h>
#include <WidgetManager.h>
#include <TextWidget.h>

#define PAGE_MANGER_PAGE_LIST_SIZE              10
#define PAGE_MANAGER_CALL_STACK_SIZE            4

#define PAGE_MANAGER_NEXT_PAGE_EVENT_ID         0x00001
#define PAGE_MANAGER_BACK_PAGE_EVENT_ID         0x00002

class Page;

typedef struct {
    String name;
    Page *page;
    uint8_t level;
} PageItem;

class PageManager
{

public:
    PageManager(M5StickC *m5, uint16_t width, uint16_t height);
    void build();
    void add(String name, Page *page, uint8_t level);
    void next();
    void draw();
    void processEvent(uint16_t eventId);
    void loop();

    M5StickC* getM5() { return _m5; }
    void selectPage(String name);
    void pushPage(String name);
    void popPage();

    void setPageIndex(uint8_t index) { _pageIndex = index; }
    uint8_t getPageIndex() const { return _pageIndex; }
    uint8_t getLevel() const { return _level; }

protected:
    void loadWidgets();
    uint8_t getIndexFromName(String name);
    uint8_t getPageCountAtLevel(uint8_t level);
    uint8_t getPagePositionAtLevel(uint8_t position, uint8_t level);
    void pushCallStack(uint8_t index);
    uint8_t popCallStack();

private:
    M5StickC *_m5;
    PageItem _pageList[PAGE_MANGER_PAGE_LIST_SIZE];
    uint8_t _pageCount;
    uint8_t _callStack[PAGE_MANAGER_CALL_STACK_SIZE];
    uint8_t _stackCount;
    uint8_t _pageIndex;
    uint8_t _level;
    uint16_t _width;
    uint16_t _height;
    WidgetManager _widgetManager;
    EventQueue _eventQueue;
    TextWidget _nextPageWidget;
    TextWidget _backPageWidget;

};

#endif          // PAGE_MANAGER_H
