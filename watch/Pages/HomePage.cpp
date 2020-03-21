#include <TimeLib.h>
#include "HomePage.h"

HomePage::HomePage(PageManager *manager):
Page(manager),
_clock(HOME_PAGE_CLOCK_RADIUS) {

}

void HomePage::init() {

}

void HomePage::draw(M5Display *lcd) {
    _clock.draw(lcd, 4, 2, hour(), minute());
    lcd->setCursor(100, 0);
    lcd->setTextSize(2);
    lcd->printf("%d:%02d", hour() % 12, minute());
}

void HomePage::loadWidgets(WidgetManager *manager) {

}

void HomePage::processEvent(uint16_t eventId) {

}
