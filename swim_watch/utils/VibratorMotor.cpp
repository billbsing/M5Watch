#include "M5Watch.h"
#include "VibratorMotor.h"

VibratorMotor::VibratorMotor(uint8_t pin):
_pin(pin) {

}

void VibratorMotor::begin() {
    pinMode(_pin, OUTPUT);
    _maxCounter = 0;
    _counter = 0;
}

void VibratorMotor::signal(uint8_t counter) {
    _maxCounter = counter;
    _counter = 0;
    eventQueue.pushDelay(EVENT_VIBRATOR_MOTOR_ON, 100);
}

void VibratorMotor::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_VIBRATOR_MOTOR_ON:
            digitalWrite(_pin, HIGH);
            eventQueue.pushDelay(EVENT_VIBRATOR_MOTOR_OFF, 500);
        break;
        case EVENT_VIBRATOR_MOTOR_OFF:
            digitalWrite(_pin, LOW);
            eventQueue.pushDelay(EVENT_VIBRATOR_MOTOR_NEXT, 500);
        break;
        case EVENT_VIBRATOR_MOTOR_NEXT:
            if (_maxCounter  > 0) {
                _counter ++;
                if ( _counter < _maxCounter) {
                    eventQueue.pushDelay(EVENT_VIBRATOR_MOTOR_ON, 500);
                }
                else {
                    _counter = 0;
                    _maxCounter = 0;
                }
            }
        break;
    }
}
