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
    uint16_t avgCounter;
    float avgGyroX, avgGyroY, avgGyroZ;

};


#endif          // DATA_PAGE_H
