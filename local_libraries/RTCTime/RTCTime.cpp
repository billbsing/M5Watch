#include "RTCTime.h"
#include "M5Watch.h"

RTCTime::RTCTime() {
}

void RTCTime::read() {
    M5.Rtc.GetTime(&_rtcTime);
    M5.Rtc.GetData(&_rtcDate);
}

time_t RTCTime::setLocalTime() {
    TimeElements tm;
    time_t nowTime;
    tm.Second = _rtcTime.Seconds;
    tm.Minute = _rtcTime.Minutes;
    tm.Hour = _rtcTime.Hours;
    tm.Wday = _rtcDate.WeekDay;
    tm.Day = _rtcDate.Date;
    tm.Month = _rtcDate.Month;
    tm.Year = _rtcDate.Year;
    nowTime = makeTime(tm);
    setTime(nowTime);
    return nowTime;
}


bool RTCTime::syncTimeToLocal() {
    struct tm timeinfo;

    bool result = false;
    if ( getLocalTime(&timeinfo) ) {
        _rtcTime.Hours   = timeinfo.tm_hour;
        _rtcTime.Minutes = timeinfo.tm_min;
        _rtcTime.Seconds = timeinfo.tm_sec;
        M5.Rtc.SetTime(&_rtcTime);
        _rtcDate.WeekDay = timeinfo.tm_wday;
        _rtcDate.Date = timeinfo.tm_mday;
        _rtcDate.Month = timeinfo.tm_mon;
        _rtcDate.Year = timeinfo.tm_year;
        M5.Rtc.SetData(&_rtcDate);
        result = true;
    }
    return result;
}
