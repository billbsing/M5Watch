#include <TextWidget.h>
#include "SetSleepTimePage.h"

SetSleepTimePage::SetSleepTimePage(PageManager &manager):
Page(manager) {
}

void SetSleepTimePage::init() {
}

void SetSleepTimePage::draw(M5Display *lcd) {
    lcd->setCursor(4, 0);
    lcd->setTextSize(2);
    lcd->print("Set Sleep Time");
}

void SetSleepTimePage::loadWidgets(WidgetManager *manager) {
}

void SetSleepTimePage::processEvent(uint16_t eventId) {
}
