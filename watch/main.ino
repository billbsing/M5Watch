#include <M5StickC.h>
#include <PageManager.h>
#include <Preferences.h>

#include "RTCTime.h"

#include "HomePage.h"
#include "SettingsPage.h"
#include "SetSleepTimePage.h"
#include "PageId.h"

#define SCREEN_WIDTH                160
#define SCREEN_HEIGHT               80
#define AUTO_POWER_OFF_MILLIS       ( 1000 * 5)

#define EVENT_AUTO_POWER_OFF        0x0001
#define EVENT_BUTTON_PRESSED        0x0002

typedef struct {
    uint8_t buttonA : 1;
    uint8_t buttonB : 1;
    uint8_t buttonC : 1;
} ButtonsEnabled;


RTCTime rtcTime;

EventQueue eventQueue;
PageManager pageManager(&M5, SCREEN_WIDTH, SCREEN_HEIGHT);
HomePage homePage(&pageManager);
SettingsPage settingsPage(&pageManager);
SetSleepTimePage setSleepTime(&pageManager);
ButtonsEnabled buttonsEnabled = {true, true, true};
Preferences preferences;
uint16_t autoPowerOffTimeout;

void processButtons() {
    M5.BtnB.read();
    M5.BtnA.read();
    if ( buttonsEnabled.buttonA ) {
        if ( M5.BtnA.isPressed() ) {
            buttonsEnabled.buttonA = false;
            pageManager.rasieEventOnFocus(&eventQueue);
        }
    }
    if ( M5.BtnA.isReleased() ) {
        buttonsEnabled.buttonA = true;
    }
    if ( buttonsEnabled.buttonB ) {
        if ( M5.BtnB.isPressed() ) {
            buttonsEnabled.buttonB = false;
            pageManager.nextFocus();
        }
    }
    if ( M5.BtnB.isReleased() ) {
        buttonsEnabled.buttonB = true;
    }

    if ( buttonsEnabled.buttonC ) {
        if ( M5.Axp.GetBtnPress() ) {
            buttonsEnabled.buttonC = false;
            M5.Axp.PowerOff();
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
            case EVENT_BUTTON_PRESSED:
                eventQueue.remove(EVENT_AUTO_POWER_OFF);
                eventQueue.push(EVENT_AUTO_POWER_OFF, autoPowerOffTimeout);
            break;
            break;
        }
        pageManager.processEvent(eventId);
    }
}

void setup() {
    Serial.begin(15200);
    while(!Serial) { }
    Serial.println("Begin");

    preferences.begin("preferences", false);
    autoPowerOffTimeout = preferences.getUShort("autoPowerOffTimeout", AUTO_POWER_OFF_MILLIS);
    eventQueue.push(EVENT_AUTO_POWER_OFF, autoPowerOffTimeout);
    preferences.end();

    pageManager.add(PAGE_ID_HOME, &homePage, 0);
    pageManager.add(PAGE_ID_SETTINGS, &settingsPage, 0);
    pageManager.add(PAGE_ID_SET_SLEEP, &setSleepTime, 1);
    pageManager.build();

    M5.begin();
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);

    rtcTime.read(M5.Rtc);
    rtcTime.setLocalTime();

    pageManager.draw();
}

void loop() {
    processEvents();
    delay(100);
}
