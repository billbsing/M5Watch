// PageManager


#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include <Arduino.h>
#include <M5StickC.h>

#define PAGE_MANGER_PAGE_LIST_SIZE       10

class Page;

class PageManager
{

public:
    PageManager();
    void add(Page *page);
    void next();
    void show(M5Display &lcd);

private:
    Page *_pageList[PAGE_MANGER_PAGE_LIST_SIZE];
    uint8_t _count;
    uint8_t _position;

};

#endif          // PAGE_MANAGER_H
