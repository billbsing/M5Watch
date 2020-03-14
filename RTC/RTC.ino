#include <M5StickC.h>
#include <Wifi.h>
#include <WifiUDP.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include "private.h"

#define DEBUG_SERIAL


WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP, "sg.pool.ntp.org", 8 * SECS_PER_HOUR);
bool isSyncTime;
RTC_TimeTypeDef rtcTimeStruct;
RTC_DateTypeDef rtcDateStruct;

void showTime() {
    M5.Rtc.GetTime(&rtcTimeStruct);
    M5.Rtc.GetData(&rtcDateStruct);
    M5.Lcd.setCursor(0, 2);
    M5.Lcd.printf("Data: %04d-%02d-%02d\n",rtcDateStruct.Year, rtcDateStruct.Month,rtcDateStruct.Date);
    // M5.Lcd.printf("Week: %d\n",RTC_DateStruct.WeekDay);
    M5.Lcd.printf("Time: %02d : %02d : %02d\n",rtcTimeStruct.Hours, rtcTimeStruct.Minutes, rtcTimeStruct.Seconds);
    if ( isSyncTime) {
        M5.Lcd.print("Sync");
    }
    else {
        M5.Lcd.print("      ");
    }
//    M5.Lcd.printf("Data: %04d-%02d-%02d\n", year(), month(), day());
//    M5.Lcd.printf("Time: %02d : %02d : %02d\n", hour(), minute(), second());
//    M5.Lcd.printf("%1d", ntpClient.getEpochTime());
}

bool syncTime() {
    bool result = false;
    if ( ntpClient.getEpochTime() > SECS_YR_2000) {
        #ifdef DEBUG_SERIAL
        Serial.println("Sync time");
        #endif
        setTime(ntpClient.getEpochTime());
        rtcTimeStruct.Hours   = hour();
        rtcTimeStruct.Minutes = minute();
        rtcTimeStruct.Seconds = second();
        M5.Rtc.SetTime(&rtcTimeStruct);
        rtcDateStruct.WeekDay = weekday();
        rtcDateStruct.Month = month();
        rtcDateStruct.Date = day();
        rtcDateStruct.Year = year();
        M5.Rtc.SetData(&rtcDateStruct);
        result = true;
    }
}
void setup() {


    #ifdef DEBUG_SERIAL
    Serial.begin(115200);
    Serial.setTimeout(2000);

    // Wait for serial to initialize.
    while(!Serial) { }
    Serial.println("Start Debug");

    #endif

    M5.begin();
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);

    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(40, 0, 2);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    ntpClient.begin();
    isSyncTime = false;
    // ntpClient.setOnSync(onSync);
}

void loop() {
    showTime();
    ntpClient.update();
    if ( !isSyncTime ) {
        isSyncTime = syncTime();
    }
    M5.BtnA.read();
    if ( M5.BtnA.isPressed() ) {
        isSyncTime = false;
    }
    delay(500);
}
