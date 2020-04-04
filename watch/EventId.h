
#ifndef EVENT_IDS_h
#define EVENT_IDS_h


#define EVENT_AUTO_POWER_OFF                        0x0001
#define EVENT_NEXT_WIDGET_FOCUS                     0x0002
#define EVENT_CLICK_ON_FOCUS                        0x0003
#define EVENT_DISPLAY_OFF                           0x0004
#define EVENT_WIFI_CONNECT                          0x0005
#define EVENT_WIFI_DISCONNECT                       0x0006
#define EVENT_WIFI_CONNECTED                        0x0007
#define EVENT_WIFI_DISCONNECTED                     0x0008


// RTCTime
#define EVENT_RTC_SYNC_TIME                         0x0010
#define EVENT_RTC_SYNC_TIME_DONE                    0x0011

// Power Status
#define EVENT_READ_POWER_STATUS                     0x0020

// DataRecorder
#define EVENT_DATA_ON_CHANGE                        0x0030
#define EVENT_DATA_START                            0x0031
#define EVENT_DATA_STOP                             0x0032
#define EVENT_DATA_UPLOAD                           0x0033
#define EVENT_DATA_RESET                            0x0034


// Page Event Id from here onwards
#define EVENT_PAGE_START_ID                         0x8000


#endif          // EVENT_IDS_h
