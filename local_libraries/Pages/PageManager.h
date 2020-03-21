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
#define PAGE_MANAGER_START_EVENT_ID             0x0800

class Page;

typedef struct {
    uint8_t pageId;
    uint8_t pageGroup;
    Page *page;
} PageItem;


class PageManager
{

public:
    PageManager(M5StickC *m5, uint16_t width, uint16_t height);
    void build();
    void add(uint8_t pageId, Page *page, uint8_t pageGroup);
    void nextPage();
    void draw();
    void processEvent(uint16_t eventId);

    M5StickC* getM5() { return _m5; }
    void selectPage(uint8_t pageId);
    void pushPage(uint8_t pageId);
    void popPage();

    void setPageIndex(uint8_t index);
    uint8_t getPageIndex() const { return _pageIndex; }
    uint8_t getpageGroup() const { return _pageGroup; }
    uint16_t getNextEventId();

    void rasieEventOnFocus(EventQueue *eventQueue);
    void nextFocus();

protected:
    void loadWidgets();
    uint8_t getIndexFromPageId(uint8_t pageId);
    uint8_t getPageCountInGroup(uint8_t pageGroup);
    uint8_t getPagePositionInGroup(uint8_t position, uint8_t pageGroup);
    void pushCallStack(uint8_t index);
    uint8_t popCallStack();

private:
    M5StickC *_m5;
    PageItem _pageList[PAGE_MANGER_PAGE_LIST_SIZE];
    uint8_t _pageCount;
    uint8_t _callStack[PAGE_MANAGER_CALL_STACK_SIZE];
    uint8_t _stackCount;
    uint8_t _pageIndex;
    uint8_t _pageGroup;
    uint16_t _width;
    uint16_t _height;
    WidgetManager _widgetManager;
    TextWidget _nextPageWidget;
    TextWidget _backPageWidget;
    uint16_t _eventIndex;

};

#endif          // PAGE_MANAGER_H
