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
    lcd->setCursor(140, 55);
    lcd->setTextSize(1);
    powerStatus.read();
    if ( powerStatus.isCharging() ) {
        lcd->printf("%d", powerStatus.getInputPowerStatus());
    }
    else {
        lcd->printf("%d%%", int(powerStatus.getBatteryPercent()));
    }
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

void HomePage::end() {
    eventQueue.remove(EVENT_READ_POWER_STATUS);
}

void HomePage::loadWidgets(WidgetManager *manager) {
}

void HomePage::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_READ_POWER_STATUS:
            debug.print("%04X", eventId);
            drawPowerStatus(getLcd());
            eventQueue.pushDelay(EVENT_READ_POWER_STATUS, 1000, true);
        break;
    }
}
