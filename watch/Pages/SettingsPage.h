// TextPage

#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H


#include "Page.h"

#define SETTINGS_PAGE_MENU_SLEEP_TIME_EVENT_ID              0x01
#define SETTINGS_PAGE_MENU_POWER_EVENT_ID                   0x02


class SettingsPage: public Page
{
public:
    SettingsPage() {;}

    void loadWidgets(WidgetManager *manager);
    void show(M5Display &lcd);
    void processEvent(uint16_t eventId);

private:

};


#endif          // SETTINGS_PAGE_H
