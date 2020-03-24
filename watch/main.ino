#include <M5StickC.h>
#include <PageManager.h>
#include <Preferences.h>
#include "RTCTime.h"

#include "HomePage.h"
#include "SettingsPage.h"
#include "SetSleepTimePage.h"
#include "SyncTimePage.h"

#include "Settings.h"
#include "SerialDebug.h"
#include "WiFiManager.h"

#include "PageId.h"
#include "EventId.h"

#define SCREEN_WIDTH                160
#define SCREEN_HEIGHT               80


#define MODULE_ID_DEBUG             0x01

typedef struct {
    uint8_t buttonA : 1;
    uint8_t buttonB : 1;
    uint8_t buttonC : 1;
} ButtonsEnabled;


PageManager pageManager(&M5, SCREEN_WIDTH, SCREEN_HEIGHT);
HomePage homePage(&pageManager);
SettingsPage settingsPage(&pageManager);
SetSleepTimePage setSleepTimePage(&pageManager);
SyncTimePage syncTimePage(&pageManager);

RTCTime rtcTime;
EventQueue eventQueue;
ButtonsEnabled buttonsEnabled = {true, true, true};
Settings settings("preferences");
SerialDebug debug;
WiFiManager wifiManager;

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
        switch( eventId ) {
            case EVENT_AUTO_POWER_OFF:
                M5.Axp.PowerOff();
            break;
            case EVENT_NEXT_WIDGET_FOCUS:
                pageManager.nextFocus();
                eventQueue.push(EVENT_AUTO_POWER_OFF, autoPowerOffTimeout, true);
            break;
            case EVENT_CLICK_ON_FOCUS:
                pageManager.rasieEventOnFocus(&eventQueue);
                eventQueue.push(EVENT_AUTO_POWER_OFF, autoPowerOffTimeout, true);
            break;
            case EVENT_DISPLAY_OFF:
                M5.Axp.SetLDO2(false);
            break;
        }
        pageManager.processEvent(eventId);
        wifiManager.processEvent(eventId);
    }
}

void setup() {
    debug.begin(15200);
    debug.print("setup");

    settings.begin(true);
    autoPowerOffTimeout = settings.getAutoPowerOffTimeout();
    settings.end();
    eventQueue.push(EVENT_AUTO_POWER_OFF, autoPowerOffTimeout);

    pageManager.add(PAGE_ID_HOME, &homePage, 0);
    pageManager.add(PAGE_ID_SETTINGS, &settingsPage, 0);
    pageManager.add(PAGE_ID_SET_SLEEP, &setSleepTimePage, 1);
    pageManager.add(PAGE_ID_SYNC_TIME, &syncTimePage, 2);
    pageManager.build();

    M5.begin();
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);

    rtcTime.read(M5.Rtc);
    rtcTime.setLocalTime();

    pageManager.draw();
    // eventQueue.push(EVENT_DISPLAY_OFF, 2000);
}

void loop() {
    processButtons();
    processEvents();
    wifiManager.loop();
    delay(100);
}
