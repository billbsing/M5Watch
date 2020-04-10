
#ifndef EVENT_IDS_h
#define EVENT_IDS_h

// General Events

#define EVENT_AUTO_POWER_OFF                        0x0001
#define EVENT_NEXT_WIDGET_FOCUS                     0x0002
#define EVENT_CLICK_ON_FOCUS                        0x0003
#define EVENT_DISPLAY_OFF                           0x0004

// WiFi Events
#define EVENT_WIFI_CONNECT                          0x0010
#define EVENT_WIFI_DISCONNECT                       0x0011
#define EVENT_WIFI_CONNECTED                        0x0012
#define EVENT_WIFI_DISCONNECTED                     0x0013

// RTCTime
#define EVENT_RTC_SYNC_TIME                         0x0020
#define EVENT_RTC_SYNC_TIME_DONE                    0x0021

// Power Status
#define EVENT_READ_POWER_STATUS                     0x0030

// DataRecorder
#define EVENT_DATA_ON_CHANGE                        0x0040
#define EVENT_DATA_INIT                             0x0041
#define EVENT_DATA_START                            0x0042
#define EVENT_DATA_STOP                             0x0043
#define EVENT_DATA_UPLOAD                           0x0044
#define EVENT_DATA_DELETE                           0x0045
#define EVENT_DATA_SAVE                             0x0046
#define EVENT_DATA_START_UPLOAD_ITEM                0x0047
#define EVENT_DATA_UPLOAD_ITEM                      0x0047

// Page Event Id from here onwards
#define EVENT_PAGE_START_ID                         0x8000


#endif          // EVENT_IDS_h
