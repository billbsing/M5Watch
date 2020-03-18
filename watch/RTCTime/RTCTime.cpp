#include "RTCTime.h"


RTCTime::RTCTime() {
}

void RTCTime::read(RTC &rtc) {
    rtc.GetTime(&_rtcTime);
    rtc.GetData(&_rtcDate);
}

time_t RTCTime::setLocalTime() {
    setTime(_rtcTime.Hours, _rtcTime.Minutes, _rtcTime.Seconds, \
                _rtcDate.Date, _rtcDate.Month, _rtcDate.Year);
    return now();
}
