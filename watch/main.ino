#include <M5StickC.h>

#include "PageManager.h"
#include "TextPage.h"
#include "RTCTime.h"

#define SCREEN_WIDTH                160
#define SCREEN_HEIGHT               80


RTCTime rtcTime;

PageManager pageManager(SCREEN_WIDTH, SCREEN_HEIGHT);
TextPage homePage("Home");
TextPage resetPage("Reset");

void setup() {
    pageManager.add(&homePage);
    pageManager.add(&resetPage);
    M5.begin();
    rtcTime.setRTC(&M5.Rtc);
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);
    pageManager.setLCD(&M5.Lcd);
    pageManager.show();
}

void loop() {
    M5.BtnB.read();
    if ( M5.BtnB.isPressed() ) {
        pageManager.next();
    }
    delay(500);
}
