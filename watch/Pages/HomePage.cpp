#include <TimeLib.h>
#include "M5Watch.h"
#include "HomePage.h"

HomePage::HomePage(PageManager *manager):
Page(manager),
_clock(HOME_PAGE_CLOCK_RADIUS) {
}

void HomePage::init() {
}

void HomePage::drawPowerStatus(M5Display *lcd) {
    lcd->setCursor(80, 30);
    lcd->setTextSize(1);
    lcd->print(powerStatus.getStatus());
}

void HomePage::draw(M5Display *lcd) {
    _clock.draw(lcd, 4, 2, hour(), minute());
    lcd->setCursor(100, 0);
    lcd->setTextSize(2);
    lcd->printf("%d:%02d", hour() % 12, minute());
    drawPowerStatus(lcd);
}

void HomePage::begin() {
    eventQueue.pushDelay(EVENT_READ_POWER_STATUS, 1000, true);
}

void HomePage::loadWidgets(WidgetManager *manager) {
}

void HomePage::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_READ_POWER_STATUS:
            drawPowerStatus(getLcd());
            eventQueue.pushDelay(EVENT_READ_POWER_STATUS, 500, true);
        break;
    }
}
