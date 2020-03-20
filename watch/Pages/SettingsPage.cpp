#include <TextWidget.h>
#include "SettingsPage.h"

#define MENU_ITEM_WIDTH                 100
#define MENU_ITEM_HEIGHT                15


SettingsPage::SettingsPage(PageManager &manager):
Page(manager) {
}

void SettingsPage::init() {
    uint16_t y = 20;
    _menuSetSleep = TextWidget(getNextEventId(), 4, y, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, 4, 4, "Sleep Time");
    y += MENU_ITEM_HEIGHT + 2;
    _menuPowerOff = TextWidget(getNextEventId(), 4, y, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, 4, 4, "Power Off");
}

void SettingsPage::draw(M5Display *lcd) {
    lcd->setCursor(4, 0);
    lcd->setTextSize(2);
    lcd->print("Settings");
}

void SettingsPage::loadWidgets(WidgetManager *manager) {
    manager->add(&_menuSetSleep);
    manager->add(&_menuPowerOff);
}

void SettingsPage::processEvent(uint16_t eventId) {
    if ( _menuPowerOff.isEventId(eventId)) {
        getM5()->Axp.PowerOff();
    }

    if ( _menuSetSleep.isEventId(eventId)) {
        pushPage("SetSleepTime");
    }
}
