// TextPage

#ifndef SET_SLEEP_TIME_PAGE_H
#define SET_SLEEP_TIME_PAGE_H


#include <Page.h>
#include <TextWidget.h>


class SetSleepTimePage: public Page
{
public:
    SetSleepTimePage(PageManager *manager);

    void init();
    void loadWidgets(WidgetManager *manager);
    void draw(M5Display *lcd);
    void processEvent(uint16_t eventId);

private:

    int8_t _value;
    TextWidget _decrementWidget;
    TextWidget _incrementWidget;
};


#endif          // SET_SLEEP_TIME_PAGE_H
