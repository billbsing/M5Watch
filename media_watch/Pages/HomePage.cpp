#include <TimeLib.h>
#include "MediaWatch.h"
#include "HomePage.h"

HomePage::HomePage():
_clock(HOME_PAGE_CLOCK_RADIUS) {

}

void HomePage::init() {
}

void HomePage::drawPowerStatus(M5Display *lcd) {
    lcd->setCursor(100, 55);
    lcd->setTextSize(1);
    powerStatus.read();
    if ( powerStatus.isCharging() ) {
        lcd->printf("%d / %1.2f", powerStatus.getInputPowerStatus(), powerStatus.getBatteryVoltage());
    }
    else {
        lcd->printf("%d%% / %1.2f", int(powerStatus.getBatteryPercent()), powerStatus.getBatteryVoltage());
    }
}

void HomePage::draw(M5Display *lcd) {
    _clock.draw(lcd, 4, 2, hour(), minute());
    lcd->setCursor(100, 0);
    lcd->setTextSize(2);
    lcd->printf("%d:%02d", hourFormat12(), minute());
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
            drawPowerStatus(getLcd());
            eventQueue.pushDelay(EVENT_READ_POWER_STATUS, 1000, true);
        break;
    }
}
