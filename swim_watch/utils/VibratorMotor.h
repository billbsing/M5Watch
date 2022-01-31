/*

Settings

*/

#ifndef VIBRATOR_MOTOR_H
#define VIBRATOR_MOTOR_H

#include <Arduino.h>




class VibratorMotor {
public:
    VibratorMotor(uint8_t pin);
    void begin();
    void signal(uint8_t counter);
    void processEvent(uint16_t eventId);
private:
    uint8_t _pin;
    uint8_t _counter;
    uint8_t _maxCounter;

};



#endif              // VIBRATOR_MOTOR_H
