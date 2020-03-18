// Page

#ifndef PAGE_H
#define PAGE_H

#include <Arduino.h>
#include <M5StickC.h>
#include "WidgetManager.h"

class Page
{
public:
    Page();
    virtual void loadWidgets(WidgetManager *manager) = 0;
    virtual void show(M5Display &lcd) = 0;
    virtual void processEvent(uint16_t eventId) = 0;

protected:
    uint8_t getIndex() { return _index; }


private:
    uint8_t _index;
};
#endif          // PAGE_H
