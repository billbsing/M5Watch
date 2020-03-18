#include <TimeLib.h>
#include "HomePage.h"

HomePage::HomePage():
_clock(HOME_PAGE_CLOCK_RADIUS) {

}
void HomePage::show(M5Display &lcd) {
    _clock.draw(lcd, 4, 2, hour(), minute());
    lcd.setCursor(80, 0);
    M5.Lcd.setTextSize(2);
    lcd.printf("%d:%02d", hour(), minute());
}

void HomePage::loadWidgets(WidgetManager *manager) {

}

void HomePage::processEvent(uint16_t eventId) {

}
