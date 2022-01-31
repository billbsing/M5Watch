/*

    PowerStatus.h

*/

#ifndef POWER_STATUS_H
#define POWER_STATUS_H

#include <M5StickC.h>


class PowerStatus
{
public:
    PowerStatus();

    void read();
    String getStatus();
    uint8_t getChargingStatus() { return _chargeStatus; }
    uint8_t getInputPowerStatus() { return _inputPowerStatus; }
    float getBatteryVoltage() { return _batteryVoltage; }
    float getBatteryPercent() { return _batteryPercent; }
    bool isCharging() { return _inputPowerStatus > 1; }

private:
    uint8_t _chargeStatus;
    uint8_t _inputPowerStatus;
    float _batteryVoltage;
    float _batteryPercent;

};



#endif                  // POWER_STATUS_H
