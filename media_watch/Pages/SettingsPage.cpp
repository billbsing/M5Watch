#include <TextWidget.h>
#include "SettingsPage.h"
#include "MediaWatch.h"

#define MENU_ITEM_WIDTH                 75
#define MENU_ITEM_HEIGHT                12
#define MENU_ITEM_PADDING               2

SettingsPage::SettingsPage() {

}

void SettingsPage::init() {
    uint16_t y = 12;
    uint16_t x = 4;
    _menuSetSleep.setPosition(x, y);
    _menuSetSleep.setSize(MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT);
    _menuSetSleep.setText("Sleep Time");

    y += MENU_ITEM_HEIGHT + MENU_ITEM_PADDING;
    _menuPowerOff.setPosition(x, y);
    _menuPowerOff.setSize(MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT);
    _menuPowerOff.setText("Power Off");

//    y = 14;
//    x = 85;
    y += MENU_ITEM_HEIGHT + MENU_ITEM_PADDING;
    _menuWifiSettings.setPosition(x, y);
    _menuWifiSettings.setSize(MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT);
    _menuWifiSettings.setText("Wifi");
}

void SettingsPage::begin() {
}

void SettingsPage::end() {
}

void SettingsPage::loadWidgets(WidgetManager *manager) {
    manager->add(&_menuSetSleep);
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
    if ( _menuPowerOff.isEventId(eventId)) {
        getM5()->Axp.PowerOff();
    }
    if ( _menuWifiSettings.isEventId(eventId)) {
        pushPage(PAGE_ID_WIFI_PAGE);
    }

}
