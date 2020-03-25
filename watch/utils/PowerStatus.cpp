#include "PowerStatus.h"


PowerStatus::PowerStatus(AXP192 *axp):
_axp(axp) {

}

String PowerStatus::getStatus() {
    char buffer[40];
    uint8_t value = _axp->GetBatteryChargingStatus();
    value = _axp->GetInputPowerStatus();
    float batteryVoltage = _axp->GetBatVoltage();
    sprintf(buffer, "Battery");
    if ( value > 1 ) {
        sprintf(buffer,"Charging %d", value);
    }
    else {
        sprintf(buffer, "Battery %0.1f", batteryVoltage);
    }
    return String(buffer);
}
