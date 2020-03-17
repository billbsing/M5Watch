#include <M5StickC.h>
#include <WiFi.h>
#include <WiFiUdp.h>
//#include <NTPClient.h>
#include <TimeLib.h>
#include <FS.h>
#include <ModuleManager.h>
#include <DebugModule.h>

#include "private.h"

#define DEBUG_SERIAL

#define LED_PIN                     10
#define SCREEN_WIDTH                160
#define SCREEN_HEIGHT               80
#define CLOCK_RADIUS                36
#define PI                          3.1415926535897932384626433832795
#define DISPLAY_TIMEOUT             (10 * 1000)

#define TIME_DATA_FILE              "/timeData.dat"
#define IS_NETWORK_TIME
#define NTP_GMT_OFFSET_SECONDS      (8 * SECS_PER_HOUR)
#define NTP_DAYLIGHT_SAVING_OFFSET  0
#define NTP_SERVER                  "sg.pool.ntp.org"

//WiFiUDP ntpUDP;
//NTPClient ntpClient(ntpUDP, "sg.pool.ntp.org", 8 * SECS_PER_HOUR);
bool isSyncTime;
RTC_TimeTypeDef rtcTimeStruct;
RTC_DateTypeDef rtcDateStruct;
uint8_t lastDisplayMinute;

typedef struct {
    time_t startTime;
    time_t lastTime;
} TimeData;

TimeData timeData;

time_t displayTimeout;
bool isDisplaySleeping;

#define     DEBUG_MODULE_ID     0x01

DebugModule debugModule(DEBUG_MODULE_ID, "debug", 15200);
ModuleManager moduleManager;

void saveTimeData() {

    SPIFFS.begin();
    File f = SPIFFS.open(TIME_DATA_FILE, "w");
    if ( f ) {
        f.write((uint8_t *)&timeData, sizeof(TimeData));
/*
        uint8_t *ptr = (uint8_t *) &timeData;
        for (uint16_t i = 0 ; i <sizeof(TimeData); i++ ) {
            f.write(*ptr);
            ptr ++;
        }
*/
        Serial.println(timeData.startTime);
        Serial.println(timeData.lastTime);

        f.close();
    }
    SPIFFS.end();
}

void setTimeData() {
    M5.Rtc.GetTime(&rtcTimeStruct);
    M5.Rtc.GetData(&rtcDateStruct);
    setTime(rtcTimeStruct.Hours, rtcTimeStruct.Minutes, rtcTimeStruct.Seconds, \
    rtcDateStruct.Date, rtcDateStruct.Month, rtcDateStruct.Year);

    if ( timeData.startTime == 0) {
        timeData.startTime = now();
    }
    timeData.lastTime = now();
}
void readTimeData() {
    SPIFFS.begin();
    memset(&timeData, 0, sizeof(TimeData));
    if (SPIFFS.exists(TIME_DATA_FILE)) {
        File f = SPIFFS.open(TIME_DATA_FILE, "r");
        if ( f ) {
            f.readBytes((char *) &timeData, sizeof(TimeData));
/*
            uint8_t *ptr = (uint8_t *) &timeData;
            for (uint16_t i = 0 ; i <sizeof(TimeData); i++ ) {
                *ptr = f.read();
                ptr ++;
            }
*/
            f.close();
        }
        Serial.println(timeData.startTime);
        Serial.println(timeData.lastTime);
    }
    SPIFFS.end();
}

void clearTimeData() {
    Serial.println("clear time");
/*
    SPIFFS.begin();
    SPIFFS.format();
    SPIFFS.end();
*/
    timeData.startTime = now();
    saveTimeData();
}

void checkDisplaySleep() {
    float gx,gy,gz;
    M5.IMU.getAccelData(&gx, &gy, &gz);
    if ( gx> 1 ) {
/*
        Serial.print(gx);
        Serial.print(" ");
        Serial.print(gy);
        Serial.print(" ");
        Serial.println(gz);
*/
        displayTimeout = millis() + DISPLAY_TIMEOUT;
        if ( isDisplaySleeping) {
            M5.Axp.ScreenBreath(80);
//            M5.Lcd.begin();
            isDisplaySleeping = false;
            lastDisplayMinute = 0xFF;
        }
    }
    if ( displayTimeout < millis() && !isDisplaySleeping) {
        // M5.Lcd.sleep();
        //M5.Axp.PowerOff();
        M5.Axp.ScreenBreath(0);
        isDisplaySleeping = true;
    }
}
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
    M5.Lcd.drawLine(clockLeft, clockTop, hourToX, hourToY, color);
}
void showClock() {
    int clockLeft = SCREEN_WIDTH - CLOCK_RADIUS - 10;
    int clockTop = CLOCK_RADIUS + 2;
    // M5.Lcd.fillRect(clockLeft - CLOCK_RADIUS, clockTop - CLOCK_RADIUS,CLOCK_RADIUS * 2, CLOCK_RADIUS*2, BLACK);
    M5.Lcd.drawCircle(clockLeft, clockTop, CLOCK_RADIUS, RED);
    for ( int minute = 0; minute < 60 ; minute += 5) {
        int fromX = clockLeft + calcMinuteToX(minute, CLOCK_RADIUS - 1);
        int toX = clockLeft + calcMinuteToX(minute, CLOCK_RADIUS);
        int fromY = clockTop + calcMinuteToY(minute, CLOCK_RADIUS - 1);
        int toY = clockTop + calcMinuteToY(minute, CLOCK_RADIUS);

        // M5.Lcd.drawLine(fromX, fromY, toX, toY, WHITE);
        M5.Lcd.fillCircle(toX, toY, 1, WHITE);
    }
    // int totalHourMinutes = (rtcTimeStruct.Hours * 60) + rtcTimeStruct.Minutes;
    //int hourInMinutes = map(totalHourMinutes, 0, 1440, 0 , 60);
    int hourInMinutes = (rtcTimeStruct.Hours % 12) * 5;
    showClockHand(hourInMinutes, CLOCK_RADIUS / 2, 6, 4, GREEN);
    showClockHand(rtcTimeStruct.Minutes, CLOCK_RADIUS - 5, 4, 4, YELLOW);
    // M5.Lcd.fillCircle(clockLeft, clockTop, 4, BLACK);
}

void showTime() {
    M5.Rtc.GetTime(&rtcTimeStruct);
    M5.Rtc.GetData(&rtcDateStruct);
    if ( lastDisplayMinute != rtcTimeStruct.Minutes && !isDisplaySleeping) {
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, SCREEN_HEIGHT - 20);
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
        setTimeData();

        int seconds = timeData.lastTime - timeData.startTime;
        int hours = floor(seconds / 3600);
            seconds -= hours * 3600;
        int minutes = floor(seconds / 60);;
            seconds -= minutes * 60;

        M5.Lcd.setTextSize(1);
        M5.Lcd.setCursor(5, 2);
        M5.Lcd.printf("%d:%02d", hours, minutes);
        lastDisplayMinute = rtcTimeStruct.Minutes;

        M5.Lcd.setCursor(5, 20);
        uint8_t inputPower = M5.Axp.GetInputPowerStatus();
        uint8_t chargeStatus = M5.Axp.GetBatteryChargingStatus();
        float batteryPower = M5.Axp.GetBatPower();
        M5.Lcd.printf("%d %d %0.1f", inputPower, chargeStatus, batteryPower);
        if ( inputPower <= 1 ) {
            saveTimeData();
        }
    }
//    M5.Lcd.printf("Bat power %.3fmw", M5.Axp.GetBatPower());
    // M5.Lcd.printf("%d", M5.Axp.GetInputPowerStatus());

//    M5.Lcd.printf("Data: %04d-%02d-%02d\n", year(), month(), day());
//    M5.Lcd.printf("Time: %02d : %02d : %02d\n", hour(), minute(), second());
//    M5.Lcd.printf("%1d", ntpClient.getEpochTime());
}

bool syncTime() {
    struct tm timeinfo;

    bool result = false;
    if ( !getLocalTime(&timeinfo) ) {
        #ifdef DEBUG_SERIAL
        Serial.println("Sync time");
        #endif
        rtcTimeStruct.Hours   = timeinfo.tm_hour;
        rtcTimeStruct.Minutes = timeinfo.tm_min;
        rtcTimeStruct.Seconds = timeinfo.tm_sec;
        M5.Rtc.SetTime(&rtcTimeStruct);
        rtcDateStruct.WeekDay = timeinfo.tm_wday;
        rtcDateStruct.Month = timeinfo.tm_mon;
        rtcDateStruct.Date = timeinfo.tm_mday;
        rtcDateStruct.Year = timeinfo.tm_year;
        M5.Rtc.SetData(&rtcDateStruct);
        result = true;
    }
}

void setup() {
    moduleManager.addModule(&debugModule);

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
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);

    M5.IMU.Init();

    #ifdef IS_NETWORK_TIME
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    #endif
    isSyncTime = false;
    lastDisplayMinute = 0xFF;
    // ntpClient.setOnSync(onSync);
    readTimeData();
    isDisplaySleeping = false;
    displayTimeout = millis() + DISPLAY_TIMEOUT;

}

void loop() {
    #ifdef IS_NETWORK_TIME
    if ( WiFi.status() == WL_CONNECTED ) {
        configTime(NTP_GMT_OFFSET_SECONDS, NTP_DAYLIGHT_SAVING_OFFSET, NTP_SERVER);
    }
    #endif
    checkDisplaySleep();
    showTime();
    // ntpClient.update();
    if ( !isSyncTime ) {
//        isSyncTime = syncTime();
    }
    M5.BtnA.read();
    if ( M5.BtnA.isPressed() ) {
        isSyncTime = false;
        clearTimeData();
        lastDisplayMinute = 0xFF;
    }
    moduleManager.loop();
    // delay(500);
    M5.Axp.LightSleep(100 * 1000);
}
