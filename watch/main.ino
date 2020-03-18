#include <M5StickC.h>

#include "PageManager.h"
#include "HomePage.h"
#include "SettingsPage.h"
#include "RTCTime.h"

#define SCREEN_WIDTH                160
#define SCREEN_HEIGHT               80


RTCTime rtcTime;

PageManager pageManager(SCREEN_WIDTH, SCREEN_HEIGHT);
HomePage homePage;
SettingsPage settingsPage;

void setup() {
    pageManager.add(&homePage);
    pageManager.add(&settingsPage);
    M5.begin();
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);
    rtcTime.read(M5.Rtc);
    rtcTime.setLocalTime();

    pageManager.show(M5.Lcd);
}

void loop() {
    pageManager.loop(M5);
    delay(500);
}
