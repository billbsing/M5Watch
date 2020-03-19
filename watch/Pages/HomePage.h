// TextPage

#ifndef HOME_PAGE_H
#define HOME_PAGE_H


#include <Page.h>
#include "AnalogClock.h"

#define HOME_PAGE_CLOCK_RADIUS          36


class HomePage: public Page
{
public:
    HomePage(PageManager &manager);

    void init();
    void loadWidgets(WidgetManager *manager);
    void draw(M5Display &lcd);
    void processEvent(uint16_t eventId);

private:
    String _text;
    AnalogClock _clock;
};


#endif          // HOME_PAGE_H
