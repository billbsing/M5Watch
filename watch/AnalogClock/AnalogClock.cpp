#include "AnalogClock.h"

AnalogClock::AnalogClock(uint16_t radius):
_radius(radius) {
}

void AnalogClock::draw(M5Display *lcd, uint16_t left, uint16_t top, uint8_t hour, uint8_t minute) {
    uint16_t centreLeft = left + _radius;
    uint16_t centreTop = top + _radius;
    lcd->drawCircle(left + _radius, top + _radius, _radius, RED);
    for ( int minute = 0; minute < 60 ; minute += 5) {
        int fromX = centreLeft + calcMinuteToX(minute, _radius - 1);
        int toX = centreLeft + calcMinuteToX(minute, _radius);
        int fromY = centreTop + calcMinuteToY(minute, _radius - 1);
        int toY = centreTop + calcMinuteToY(minute, _radius);

        // M5.Lcd.drawLine(fromX, fromY, toX, toY, WHITE);
        lcd->fillCircle(toX, toY, 1, WHITE);
    }
    // int totalHourMinutes = (rtcTimeStruct.Hours * 60) + rtcTimeStruct.Minutes;
    //int hourInMinutes = map(totalHourMinutes, 0, 1440, 0 , 60);
    int hourInMinutes = (hour % 12) * 5;
    drawClockHand(lcd, centreLeft, centreTop, hourInMinutes, _radius / 2, 6, 4, GREEN);
    drawClockHand(lcd, centreLeft, centreTop, minute, _radius - 5, 4, 4, YELLOW);
}

void AnalogClock::drawClockHand(M5Display *lcd, uint16_t centreLeft , uint16_t centreTop, \
            uint16_t position, uint16_t radius, \
            uint16_t baseWidth, uint16_t baseLength, \
            uint16_t color) {
    uint16_t hourFromTopX = centreLeft + calcMinuteToX(30 + position - baseWidth, baseLength);
    uint16_t hourFromTopY = centreTop + calcMinuteToY(30 + position - baseWidth, baseLength);
    uint16_t hourFromBottomX = centreLeft + calcMinuteToX(30 + position + baseWidth, baseLength);
    uint16_t hourFromBottomY = centreTop + calcMinuteToY(30 + position + baseWidth, baseLength);
    uint16_t hourToX = centreLeft + calcMinuteToX(position, radius);
    uint16_t hourToY = centreTop + calcMinuteToY(position, radius);
    lcd->fillTriangle(hourFromTopX, hourFromTopY, hourToX, hourToY, hourFromBottomX, hourFromBottomY, color);
    lcd->drawLine(centreLeft, centreTop, hourToX, hourToY, color);
}

float AnalogClock::calcMinuteToX(int minute, int radius) {
    float angle = (((float) minute / 60) * 360) - 90;
    return radius * cos((angle * ANALOG_CLOCK_PI) / 180);
}
float AnalogClock::calcMinuteToY(int minute, int radius) {
    float angle = (((float)minute / 60) * 360) - 90;
    return radius * sin((angle * ANALOG_CLOCK_PI) / 180);
}
