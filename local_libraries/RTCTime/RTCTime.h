// RTCTIME

#ifndef RTC_TIME_H
#define RTC_TIME_H

#include <arduino.h>
#include <M5StickC.h>
#include <TimeLib.h>

class RTCTime
{
public:
    RTCTime();
    void read();
    time_t setLocalTime();
    bool syncTimeToLocal();

    RTC_TimeTypeDef &getTime() { return _rtcTime; }
    RTC_DateTypeDef &getDate() { return _rtcDate; }

private:
    RTC_TimeTypeDef _rtcTime;
    RTC_DateTypeDef _rtcDate;

};



#endif              // RTC_TIME_H
