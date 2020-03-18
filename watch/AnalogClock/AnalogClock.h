// AnalogClock

#ifndef ANALOG_CLOCK_H
#define ANALOG_CLOCK_H

#include <M5StickC.h>

#define ANALOG_CLOCK_PI                          3.1415926535897932384626433832795

class AnalogClock
{

public:
    AnalogClock(uint16_t radius);
    void draw(M5Display &lcd, uint16_t left, uint16_t top, uint8_t hour, uint8_t minute);

protected:
    void drawClockHand(M5Display &lcd, uint16_t centreLeft , uint16_t centreTop, \
            uint16_t position, uint16_t radius, \
            uint16_t baseWidth, uint16_t baseLength, \
            uint16_t color);
    float calcMinuteToX(int minute, int radius);
    float calcMinuteToY(int minute, int radius);

private:
    uint16_t _radius;
};

#endif              // ANALOG_CLOCK_H
