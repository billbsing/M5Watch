#include "PowerStatus.h"


PowerStatus::PowerStatus():
_chargeStatus(0),
_inputPowerStatus(0),
_batteryVoltage(0),
_batteryPercent(0) {

}
void PowerStatus::read() {
    _chargeStatus = M5.Axp.GetBatteryChargingStatus();
    _inputPowerStatus = M5.Axp.GetInputPowerStatus();
    _batteryVoltage = M5.Axp.GetBatVoltage();
    _batteryPercent = ((_batteryVoltage - 2.5) / 2) * 100;
}
