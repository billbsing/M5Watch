// RTCTIME

#ifndef RTC_TIME_H
#define RTC_TIME_H

#include <M5StickC.h>
#include <TimeLib.h>

class RTCTime
{
public:
    RTCTime();
    void read();
    time_t setLocalTime();

    void setRTC(RTC *rtc) { _rtc = rtc; }
    RTC_TimeTypeDef &getTime() { return _rtcTime; }
    RTC_DateTypeDef &getDate() { return _rtcDate; }

private:
    RTC *_rtc;
    RTC_TimeTypeDef _rtcTime;
    RTC_DateTypeDef _rtcDate;

};



#endif              // RTC_TIME_H
