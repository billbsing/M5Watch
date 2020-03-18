#include <M5StickC.h>

#include "PageManager.h"
#include "HomePage.h"
#include "TextPage.h"
#include "RTCTime.h"

#define SCREEN_WIDTH                160
#define SCREEN_HEIGHT               80


RTCTime rtcTime;

PageManager pageManager(SCREEN_WIDTH, SCREEN_HEIGHT);
HomePage homePage;
TextPage resetPage("Reset");

void setup() {
    pageManager.add(&homePage);
    pageManager.add(&resetPage);
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
