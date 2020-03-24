#include <TextWidget.h>
#include "SettingsPage.h"
#include "M5Watch.h"

#define MENU_ITEM_WIDTH                 80
#define MENU_ITEM_HEIGHT                12
#define MENU_ITEM_PADDING               2

SettingsPage::SettingsPage(PageManager *manager):
Page(manager) {
}

void SettingsPage::init() {
    uint16_t y = 18;
    _menuSetSleep = TextWidget(getNextEventId(), 4, y, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, 4, 2, "Sleep Time");
    y += MENU_ITEM_HEIGHT + MENU_ITEM_PADDING;
    _menuSyncTime = TextWidget(getNextEventId(), 4, y, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, 4, 2, "Sync Time");
    y += MENU_ITEM_HEIGHT + MENU_ITEM_PADDING;
    _menuPowerOff = TextWidget(getNextEventId(), 4, y, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, 4, 2, "Power Off");
}

void SettingsPage::draw(M5Display *lcd) {
    lcd->setCursor(4, 0);
    lcd->setTextSize(2);
    lcd->print("Settings");
}

void SettingsPage::loadWidgets(WidgetManager *manager) {
    manager->add(&_menuSetSleep);
    manager->add(&_menuSyncTime);
    manager->add(&_menuPowerOff);
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
