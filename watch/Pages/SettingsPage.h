// TextPage

#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H


#include "Page.h"
#include "TextWidget.h"
#define SETTINGS_PAGE_MAX_MENU_SIZE                 4


class SettingsPage: public Page
{
public:
    SettingsPage(PageManager &manager);

    void init();
    void loadWidgets(WidgetManager *manager);
    void show(M5Display &lcd);
    void processEvent(uint16_t eventId);

private:
    TextWidget _menuSetSleep;
    TextWidget _menuPowerOff;
};


#endif          // SETTINGS_PAGE_H
