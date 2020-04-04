// SwimLapPage

#ifndef DATA_PAGE_H
#define DATA_PAGE_H


#include <Page.h>
#include <TextWidget.h>


class DataPage: public Page
{
public:
    DataPage(PageManager *manager);

    void init();
    void begin();
    void end();
    void loadWidgets(WidgetManager *manager);
    void draw(M5Display *lcd);
    void processEvent(uint16_t eventId);

private:

    TextWidget _menuStartStop;
    TextWidget _menuUpload;
    TextWidget _menuDelete;

};


#endif          // DATA_PAGE_H
