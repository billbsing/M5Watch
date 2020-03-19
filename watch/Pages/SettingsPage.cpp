#include "SettingsPage.h"
#include "TextWidget.h"

SettingsPage::SettingsPage(PageManager &manager):
Page(manager) {
}

void SettingsPage::init() {
    _menuSetSleep = TextWidget(getNextEventId(), 4, 10, 30, 10, 1, 1, "Sleep Time");
    _menuPowerOff = TextWidget(getNextEventId(), 4, 20, 30, 10, 1, 1, "Power Off");
}

void SettingsPage::draw(M5Display &lcd) {
    lcd.setCursor(4, 0);
    lcd.setTextSize(2);
    lcd.print("Settings");
}

void SettingsPage::loadWidgets(WidgetManager *manager) {
    manager->add(&_menuSetSleep);
    manager->add(&_menuPowerOff);
}

void SettingsPage::processEvent(uint16_t eventId) {
    if ( _menuPowerOff.isEventId(eventId)) {
        getM5().Axp.PowerOff();
    }

    if ( _menuSetSleep.isEventId(eventId)) {
        pushPage("SetSleepTime");
    }
}
