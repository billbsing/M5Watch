#include "PowerStatus.h"


PowerStatus::PowerStatus(AXP192 *axp):
_axp(axp),
_chargeStatus(0),
_inputPowerStatus(0),
_batteryVoltage(0),
_batteryPercent(0) {

}
void PowerStatus::read() {
    _chargeStatus = _axp->GetBatteryChargingStatus();
    _inputPowerStatus = _axp->GetInputPowerStatus();
    _batteryVoltage = _axp->GetBatVoltage();
    _batteryPercent = ((_batteryVoltage - 2.5) / 2) * 100;
}
