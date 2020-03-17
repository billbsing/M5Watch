// Page

#ifndef PAGE_H
#define PAGE_H

#include <Arduino.h>
#include <M5StickC.h>

class Page
{
public:
    Page();
    virtual void show(M5Display *lcd) = 0;

protected:
    uint8_t getIndex() { return _index; }


private:
    uint8_t _index;
};
#endif          // PAGE_H
