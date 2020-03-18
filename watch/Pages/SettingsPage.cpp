#include "SettingsPage.h"
#include "TextWidget.h"

void SettingsPage::show(M5Display &lcd) {
    lcd.setCursor(4, 0);
    lcd.setTextSize(2);
    lcd.print("Settings");
}

void SettingsPage::loadWidgets(WidgetManager *manager) {
    manager->add(new TextWidget(SETTINGS_PAGE_MENU_SLEEP_TIME_EVENT_ID, 4, 10, 30, 10, "Sleep Time"));
    manager->add(new TextWidget(SETTINGS_PAGE_MENU_POWER_EVENT_ID, 4, 20, 30, 10, "Power Off"));
}

void SettingsPage::processEvent(uint16_t evendId) {

}
