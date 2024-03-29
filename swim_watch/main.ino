#include <M5StickC.h>
#include <PageManager.h>
#include <Preferences.h>

#include <RTCTime.h>
#include <PowerStatus.h>
#include <DataRecorder.h>

#include "Pages/HomePage.h"
#include "Pages/SettingsPage.h"
#include "Pages/SetSleepTimePage.h"
#include "Pages/SyncTimePage.h"
#include "Pages/DataPage.h"
#include "Pages/WiFiPage.h"
#include "Pages/SwimPage.h"

#include <Settings.h>
#include <SerialDebug.h>
#include <WiFiManager.h>

#include "PageId.h"
#include "EventId.h"
#include "private.h"

#define SCREEN_WIDTH                160
#define SCREEN_HEIGHT               80

#define NTP_GMT_OFFSET_SECONDS      (8 * SECS_PER_HOUR)
#define NTP_DAYLIGHT_SAVING_OFFSET  0
#define NTP_SERVER                  "sg.pool.ntp.org"
#define DATA_RECORDER_FILENAME      "/data.dat"

#define TEST_KEY_VALUE_DB           "/test.db"

typedef struct {
    uint8_t buttonA : 1;
    uint8_t buttonB : 1;
    uint8_t buttonC : 1;
} ButtonsEnabled;

StyleItem styles[] = {
    {STYLE_SCREEN_COLOR, BLACK},
    {STYLE_WIDGET_FOCUS_BORDER_COLOR, DARKGREY},
    {STYLE_WIDGET_BORDER_COLOR, RED},
    STYLE_END
};
StyleSheet styleSheet(styles);

PageManager pageManager(&M5, SCREEN_WIDTH, SCREEN_HEIGHT, EVENT_PAGE_START_ID, &styleSheet);
HomePage homePage;
SettingsPage settingsPage;
SetSleepTimePage setSleepTimePage;
SyncTimePage syncTimePage;
DataPage dataPage;
WiFiPage wifiPage;
SwimPage swimPage;

RTCTime rtcTime;
EventQueue eventQueue;
ButtonsEnabled buttonsEnabled = {true, true, true};
Settings settings("preferences");
SerialDebug debug;
WiFiManager wifiManager(WIFI_SSID, WIFI_PASSWORD);
PowerStatus powerStatus;
DataRecorder dataRecorder(DATA_RECORDER_FILENAME, DATA_RECORDER_SERVER_HOST, DATA_RECORDER_SERVER_PORT);

uint32_t autoPowerOffTimeout;


void processButtons() {
    M5.BtnB.read();
    M5.BtnA.read();
    if ( buttonsEnabled.buttonA ) {
        if ( M5.BtnA.isPressed() ) {
            buttonsEnabled.buttonA = false;
            eventQueue.push(EVENT_CLICK_ON_FOCUS);
        }
    }
    if ( M5.BtnA.isReleased() ) {
        buttonsEnabled.buttonA = true;
    }
    if ( buttonsEnabled.buttonB ) {
        if ( M5.BtnB.isPressed() ) {
            buttonsEnabled.buttonB = false;
            eventQueue.push(EVENT_NEXT_WIDGET_FOCUS);
        }
    }
    if ( M5.BtnB.isReleased() ) {
        buttonsEnabled.buttonB = true;
    }

    if ( buttonsEnabled.buttonC ) {
        if ( M5.Axp.GetBtnPress() ) {
            buttonsEnabled.buttonC = false;
            eventQueue.push(EVENT_AUTO_POWER_OFF, true);
        }
    }
    if ( ! M5.Axp.GetBtnPress() ) {
        buttonsEnabled.buttonC = true;
    }
}

void processEvents() {
    uint16_t eventId;
    eventId = eventQueue.pop();
    if ( eventId ) {
        debug.print("Event: %04X", eventId);
        switch( eventId ) {
            case EVENT_AUTO_POWER_OFF:
                M5.Axp.PowerOff();
            break;
            case EVENT_NEXT_WIDGET_FOCUS:
                pageManager.nextFocus();
//                eventQueue.pushDelay(EVENT_AUTO_POWER_OFF, autoPowerOffTimeout, true);
            break;
            case EVENT_CLICK_ON_FOCUS:
                pageManager.rasieEventOnFocus(&eventQueue);
//                eventQueue.pushDelay(EVENT_AUTO_POWER_OFF, autoPowerOffTimeout, true);
            break;
            case EVENT_DISPLAY_OFF:
                M5.Axp.SetLDO2(false);
            break;
            case EVENT_RTC_SYNC_TIME:
                if (rtcTime.syncTimeToLocal()) {
                    eventQueue.pushDelay(EVENT_RTC_SYNC_TIME_DONE, 2 * 1000);
                    rtcTime.setLocalTime();
                }
                else {
                    eventQueue.pushDelay(EVENT_RTC_SYNC_TIME, 1000);
                }
            break;
        }
        pageManager.processEvent(eventId);
        wifiManager.processEvent(eventId);
        dataRecorder.processEvent(eventId);
        swimPage.processEvent(eventId);
    }
}

void setup() {
    debug.begin(15200);
    debug.print("setup");

    settings.begin(true);
    autoPowerOffTimeout = settings.getAutoPowerOffTimeout();
    settings.end();
//    eventQueue.pushDelay(EVENT_AUTO_POWER_OFF, autoPowerOffTimeout);

    pageManager.init();
    pageManager.add(PAGE_ID_HOME, &homePage, PAGE_GROUP_BASE_ID);
    pageManager.add(PAGE_ID_SETTINGS, &settingsPage, PAGE_GROUP_BASE_ID);
    pageManager.add(PAGE_ID_DATA_PAGE, &dataPage, PAGE_GROUP_BASE_ID);

    pageManager.add(PAGE_ID_SET_SLEEP, &setSleepTimePage, PAGE_GROUP_SET_SLEEP_ID);
    pageManager.add(PAGE_ID_SYNC_TIME, &syncTimePage, PAGE_GROUP_SYNC_TIME_ID);
    pageManager.add(PAGE_ID_WIFI_PAGE, &wifiPage, PAGE_GROUP_WIFI_ID);
    pageManager.add(PAGE_ID_SWIM_PAGE, &swimPage, PAGE_GROUP_BASE_ID);
/*
    SPIFFS.begin(true);
    SPIFFS.format();
    SPIFFS.end();
*/
    M5.begin();
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);

    M5.MPU6886.Init();

    configTime(NTP_GMT_OFFSET_SECONDS, NTP_DAYLIGHT_SAVING_OFFSET, NTP_SERVER);

    rtcTime.read();
    rtcTime.setLocalTime();

    pageManager.refresh();


    // make sure we disconect wifi
    eventQueue.push(EVENT_WIFI_DISCONNECT);
}

void loop() {
    processButtons();
    processEvents();
    wifiManager.loop();
    dataRecorder.loop();
    delay(10);
}
