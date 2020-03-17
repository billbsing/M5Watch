#include "AnalogClock.h"

AnalogClock::AnalogClock(M5Display *lcd, uint16_t centreLeft, uint16_t centreTop, uint16_t radius):
_lcd(lcd),
_centreLeft(centreLeft),
_centreTop(centreTop),
_radius(radius) {

}

void AnalogClock::draw(uint8_t hour, uint8_t minute) {
    _lcd->drawCircle(_centreLeft, _centreTop, _radius, RED);
    for ( int minute = 0; minute < 60 ; minute += 5) {
        int fromX = _centreLeft + calcMinuteToX(minute, _radius - 1);
        int toX = _centreLeft + calcMinuteToX(minute, _radius);
        int fromY = _centreTop + calcMinuteToY(minute, _radius - 1);
        int toY = _centreTop + calcMinuteToY(minute, _radius);

        // M5.Lcd.drawLine(fromX, fromY, toX, toY, WHITE);
        _lcd->fillCircle(toX, toY, 1, WHITE);
    }
    // int totalHourMinutes = (rtcTimeStruct.Hours * 60) + rtcTimeStruct.Minutes;
    //int hourInMinutes = map(totalHourMinutes, 0, 1440, 0 , 60);
    int hourInMinutes = (hour % 12) * 5;
    drawClockHand(hourInMinutes, _radius / 2, 6, 4, GREEN);
    drawClockHand(minute, _radius - 5, 4, 4, YELLOW);
}

void AnalogClock::drawClockHand(uint16_t position, uint16_t radius, uint16_t baseWidth, uint16_t baseLength, uint16_t color) {
    uint16_t hourFromTopX = _centreLeft + calcMinuteToX(30 + position - baseWidth, baseLength);
    uint16_t hourFromTopY = _centreTop + calcMinuteToY(30 + position - baseWidth, baseLength);
    uint16_t hourFromBottomX = _centreLeft + calcMinuteToX(30 + position + baseWidth, baseLength);
    uint16_t hourFromBottomY = _centreTop + calcMinuteToY(30 + position + baseWidth, baseLength);
    uint16_t hourToX = _centreLeft + calcMinuteToX(position, radius);
    uint16_t hourToY = _centreTop + calcMinuteToY(position, radius);
    _lcd->fillTriangle(hourFromTopX, hourFromTopY, hourToX, hourToY, hourFromBottomX, hourFromBottomY, color);
    _lcd->drawLine(_centreLeft, _centreTop, hourToX, hourToY, color);
}

float AnalogClock::calcMinuteToX(int minute, int radius) {
    float angle = (((float) minute / 60) * 360) - 90;
    return radius * cos((angle * ANALOG_CLOCK_PI) / 180);
}
float AnalogClock::calcMinuteToY(int minute, int radius) {
    float angle = (((float)minute / 60) * 360) - 90;
    return radius * sin((angle * ANALOG_CLOCK_PI) / 180);
}
