/*

Settings

*/

#ifndef VIBRATE_MOTOR_H
#define VIBRATE_MOTOR_H

#include <Arduino.h>




class VibrateMotor {
public:
    VibrateMotor(uint8_t pin);
    void begin();
    void signal(uint8_t counter);
    void processEvent(uint16_t eventId);
private:
    uint8_t _pin;
    uint8_t _counter;
    uint8_t _maxCounter;

};



#endif              // VIBRATE_MOTOR_H
