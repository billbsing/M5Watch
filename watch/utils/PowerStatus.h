/*

    PowerStatus.h

*/

#ifndef POWER_STATUS_H
#define POWER_STATUS_H

#include <M5StickC.h>


class PowerStatus
{
public:
    PowerStatus(AXP192 *axp);

    String getStatus();

private:
    AXP192 *_axp;

};



#endif                  // POWER_STATUS_H
