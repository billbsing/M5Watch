// SyncTimePage

#ifndef SYNC_TIME_PAGE_H
#define SYNC_TIME_PAGE_H


#include <Page.h>
#include <TextWidget.h>

class SyncTimePage: public Page
{
public:
    SyncTimePage(PageManager *manager);

    void init();
    void begin();    
    void loadWidgets(WidgetManager *manager);
    void draw(M5Display *lcd);
    void processEvent(uint16_t eventId);

private:
    String _wifiStatus;
};


#endif          // SYNC_TIME_PAGE_H
