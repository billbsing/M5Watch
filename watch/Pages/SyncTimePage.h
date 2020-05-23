// SyncTimePage

#ifndef SYNC_TIME_PAGE_H
#define SYNC_TIME_PAGE_H


#include <Page.h>
#include <TextWidget.h>


#define SYNC_TIME_PAGE_DOT_LENGTH       8
class SyncTimePage: public Page
{
public:
    SyncTimePage();

    void init();
    void begin();
    void end();
    void loadWidgets(WidgetManager *manager);
    void draw(M5Display *lcd);
    void processEvent(uint16_t eventId);

private:
    String _wifiStatus;
    uint8_t _syncTimeCounter;
};


#endif          // SYNC_TIME_PAGE_H
