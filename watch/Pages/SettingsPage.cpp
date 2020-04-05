#include <TextWidget.h>
#include "SettingsPage.h"
#include "M5Watch.h"

#define MENU_ITEM_WIDTH                 75
#define MENU_ITEM_HEIGHT                12
#define MENU_ITEM_PADDING               2

SettingsPage::SettingsPage(PageManager *manager):
Page(manager) {
}

void SettingsPage::init() {
    uint16_t y = 12;
    uint16_t x = 4;
    _menuSetSleep = TextWidget(getNextEventId(), x, y, \
                    MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, "Sleep Time");

    y += MENU_ITEM_HEIGHT + MENU_ITEM_PADDING;
    _menuSyncTime = TextWidget(getNextEventId(), x, y, \
                    MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, "Sync Time");

    y += MENU_ITEM_HEIGHT + MENU_ITEM_PADDING;
    _menuPowerOff = TextWidget(getNextEventId(), x, y, \
                    MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, "Power Off");

//    y = 14;
//    x = 85;
    y += MENU_ITEM_HEIGHT + MENU_ITEM_PADDING;
    _menuWifiSettings = TextWidget(getNextEventId(), x, y, \
                    MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, "Wifi");
}

void SettingsPage::begin() {
}

void SettingsPage::end() {
}

void SettingsPage::loadWidgets(WidgetManager *manager) {
    manager->add(&_menuSetSleep);
    manager->add(&_menuSyncTime);
    manager->add(&_menuPowerOff);
    manager->add(&_menuWifiSettings);
}

void SettingsPage::draw(M5Display *lcd) {
    drawHeader(lcd, "Settings");
}

void SettingsPage::processEvent(uint16_t eventId) {
    if ( _menuSetSleep.isEventId(eventId)) {
        pushPage(PAGE_ID_SET_SLEEP);
    }
    if ( _menuSyncTime.isEventId(eventId)) {
        pushPage(PAGE_ID_SYNC_TIME);
    }
    if ( _menuPowerOff.isEventId(eventId)) {
        getM5()->Axp.PowerOff();
    }
}
