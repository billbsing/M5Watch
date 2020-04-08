#include "SyncTimePage.h"
#include "M5Watch.h"

SyncTimePage::SyncTimePage(PageManager *manager):
Page(manager),
_wifiStatus("Connecting") {
}

void SyncTimePage::init() {
}

void SyncTimePage::begin() {
}

void SyncTimePage::end() {
}

void SyncTimePage::loadWidgets(WidgetManager *manager) {
    eventQueue.pushDelay(EVENT_WIFI_CONNECT, 2 * 1000);
}

void SyncTimePage::draw(M5Display *lcd) {
    drawHeader(lcd, "Sync Time");

    lcd->setTextSize(1);
    lcd->setCursor(4, 30);
    lcd->print("Wifi:");
    lcd->setCursor(40, 30);
    lcd->print(_wifiStatus);
}

void SyncTimePage::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_WIFI_CONNECTED:
            _wifiStatus = "Connected";
            drawPage();
            eventQueue.pushDelay(EVENT_RTC_SYNC_TIME, 2 * 1000);
        break;
        case EVENT_WIFI_DISCONNECTED:
            _wifiStatus = "Disconnected";
            drawPage();
        break;
        case EVENT_RTC_SYNC_TIME_DONE:
            _wifiStatus = "Sync completed";
            drawPage();
            eventQueue.pushDelay(EVENT_WIFI_DISCONNECT, 2 * 1000);
        break;
    }
}
