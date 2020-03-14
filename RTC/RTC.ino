#include <M5StickC.h>
#include <Wifi.h>
#include <WifiUDP.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include "private.h"

#define DEBUG_SERIAL

#define LED_PIN                     10
#define SCREEN_WIDTH                160
#define SCREEN_HEIGHT               80
#define CLOCK_RADIUS                36
#define PI                          3.1415926535897932384626433832795

WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP, "sg.pool.ntp.org", 8 * SECS_PER_HOUR);
bool isSyncTime;
RTC_TimeTypeDef rtcTimeStruct;
RTC_DateTypeDef rtcDateStruct;
uint8_t lastDisplayMinute;

float calcMinuteToX(int minute, int radius) {
    float angle = (((float) minute / 60) * 360) - 90;
    return radius * cos((angle * PI) / 180);
}
float calcMinuteToY(int minute, int radius) {
    float angle = (((float)minute / 60) * 360) - 90;
    return radius * sin((angle * PI) / 180);
}

void showClockHand(uint16_t position, uint16_t radius, uint16_t baseWidth, uint16_t baseLength, uint16_t color) {
    uint16_t clockLeft = SCREEN_WIDTH - CLOCK_RADIUS - 10;
    uint16_t clockTop = CLOCK_RADIUS + 2;
    uint16_t hourFromTopX = clockLeft + calcMinuteToX(30 + position - baseWidth, baseLength);
    uint16_t hourFromTopY = clockTop + calcMinuteToY(30 + position - baseWidth, baseLength);
    uint16_t hourFromBottomX = clockLeft + calcMinuteToX(30 + position + baseWidth, baseLength);
    uint16_t hourFromBottomY = clockTop + calcMinuteToY(30 + position + baseWidth, baseLength);
    uint16_t hourToX = clockLeft + calcMinuteToX(position, radius);
    uint16_t hourToY = clockTop + calcMinuteToY(position, radius);
    M5.Lcd.fillTriangle(hourFromTopX, hourFromTopY, hourToX, hourToY, hourFromBottomX, hourFromBottomY, color);

}
void showClock() {
    int clockLeft = SCREEN_WIDTH - CLOCK_RADIUS - 10;
    int clockTop = CLOCK_RADIUS + 2;
    M5.Lcd.fillRect(clockLeft - CLOCK_RADIUS, clockTop - CLOCK_RADIUS,CLOCK_RADIUS * 2, CLOCK_RADIUS*2, BLACK);
    M5.Lcd.drawCircle(clockLeft, clockTop, CLOCK_RADIUS, RED);
    for ( int minute = 0; minute < 60 ; minute += 5) {
        int fromX = clockLeft + calcMinuteToX(minute, CLOCK_RADIUS - 4);
        int fromY = clockTop + calcMinuteToY(minute, CLOCK_RADIUS - 4);
        int toX = clockLeft + calcMinuteToX(minute, CLOCK_RADIUS);
        int toY = clockTop + calcMinuteToY(minute, CLOCK_RADIUS);

        M5.Lcd.drawLine(fromX, fromY, toX, toY, WHITE);
    }

    int hourInMinutes = (rtcTimeStruct.Hours % 12) * 5;
    showClockHand(hourInMinutes, CLOCK_RADIUS / 2, 6, 4, GREEN);
    showClockHand(rtcTimeStruct.Minutes, CLOCK_RADIUS - 5, 2, 4, YELLOW);
    // M5.Lcd.fillCircle(clockLeft, clockTop, 4, BLACK);
}

void showTime() {
    M5.Rtc.GetTime(&rtcTimeStruct);
    M5.Rtc.GetData(&rtcDateStruct);
    if ( lastDisplayMinute != rtcTimeStruct.Minutes) {
        M5.Lcd.setCursor(0, 2);
        M5.Lcd.setTextSize(2);
        // M5.Lcd.printf("Data: %04d-%02d-%02d\n",rtcDateStruct.Year, rtcDateStruct.Month,rtcDateStruct.Date);
        // M5.Lcd.printf("Week: %d\n",RTC_DateStruct.WeekDay);
        // M5.Lcd.printf("%02d : %02d : %02d\n",rtcTimeStruct.Hours, rtcTimeStruct.Minutes, rtcTimeStruct.Seconds);
        M5.Lcd.printf("%2d:%02d ", rtcTimeStruct.Hours % 12, rtcTimeStruct.Minutes);
        /*
        if ( rtcTimeStruct.Hours >= 12) {
            M5.Lcd.print("pm");
        }
        else {
            M5.Lcd.print("am");
        }
        */
        showClock();
        lastDisplayMinute = rtcTimeStruct.Minutes;
    }


//    M5.Lcd.printf("Bat power %.3fmw", M5.Axp.GetBatPower());
    // M5.Lcd.printf("%d", M5.Axp.GetInputPowerStatus());

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

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, 1);

    M5.begin();
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);

//    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//    ntpClient.begin();
    isSyncTime = false;
    lastDisplayMinute = 0xFF;
    // ntpClient.setOnSync(onSync);
}

void loop() {
    showTime();
    // ntpClient.update();
    if ( !isSyncTime ) {
//        isSyncTime = syncTime();
    }
    M5.BtnA.read();
    if ( M5.BtnA.isPressed() ) {
        isSyncTime = false;
    }
    // delay(500);
    M5.Axp.LightSleep(1000 * 1000);
}
