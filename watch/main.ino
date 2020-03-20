#include <M5StickC.h>
#include <PageManager.h>

#include "RTCTime.h"

#include "HomePage.h"
#include "SettingsPage.h"
#include "SetSleepTimePage.h"

#define SCREEN_WIDTH                160
#define SCREEN_HEIGHT               80


RTCTime rtcTime;

PageManager pageManager(&M5, SCREEN_WIDTH, SCREEN_HEIGHT);
HomePage homePage(pageManager);
SettingsPage settingsPage(pageManager);
SetSleepTimePage setSleepTime(pageManager);

void setup() {
    pageManager.add("Home", &homePage, 0);
    pageManager.add("Settings", &settingsPage, 0);
    pageManager.add("SetSleepTime", &setSleepTime, 1);
    pageManager.build();

    M5.begin();
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);

    rtcTime.read(M5.Rtc);
    rtcTime.setLocalTime();

    pageManager.draw();
}

void loop() {
    pageManager.loop();
    delay(500);
}
