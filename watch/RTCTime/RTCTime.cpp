#include "RTCTime.h"


RTCTime::RTCTime():
_rtc(NULL) {

}

void RTCTime::read() {
    if ( _rtc) {
        _rtc->GetTime(&_rtcTime);
        _rtc->GetData(&_rtcDate);
    }
}

time_t RTCTime::setLocalTime() {
    read();
    setTime(_rtcTime.Hours, _rtcTime.Minutes, _rtcTime.Seconds, \
                _rtcDate.Date, _rtcDate.Month, _rtcDate.Year);
    return now();
}
