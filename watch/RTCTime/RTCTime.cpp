#include "RTCTime.h"


RTCTime::RTCTime(RTC *rtc):
_rtc(rtc) {
}

void RTCTime::read() {
    _rtc->GetTime(&_rtcTime);
    _rtc->GetData(&_rtcDate);
}

time_t RTCTime::setLocalTime() {
    setTime(_rtcTime.Hours, _rtcTime.Minutes, _rtcTime.Seconds, \
                _rtcDate.Date, _rtcDate.Month, _rtcDate.Year);
    return now();
}


bool RTCTime::syncTimeToLocal() {
    struct tm timeinfo;

    bool result = false;
    if ( !getLocalTime(&timeinfo) ) {
        _rtcTime.Hours   = timeinfo.tm_hour;
        _rtcTime.Minutes = timeinfo.tm_min;
        _rtcTime.Seconds = timeinfo.tm_sec;
        _rtc->SetTime(&_rtcTime);
        _rtcDate.WeekDay = timeinfo.tm_wday;
        _rtcDate.Month = timeinfo.tm_mon;
        _rtcDate.Date = timeinfo.tm_mday;
        _rtcDate.Year = timeinfo.tm_year;
        _rtc->SetData(&_rtcDate);
        result = true;
    }
}
