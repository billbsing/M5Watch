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
    PageManager(uint16_t width, uint16_t height);
    void add(Page *page);
    void setLCD(M5Display *lcd) {_lcd = lcd;}
    void next();
    void show();

private:
    M5Display *_lcd;
    Page *_pageList[PAGE_MANGER_PAGE_LIST_SIZE];
    uint8_t _count;
    uint8_t _position;
    uint16_t _width;
    uint16_t _height;

};

#endif          // PAGE_MANAGER_H
