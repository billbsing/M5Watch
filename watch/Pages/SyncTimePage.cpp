#include "SyncTimePage.h"
#include "M5Watch.h"

SyncTimePage::SyncTimePage(PageManager *manager):
Page(manager),
_wifiStatus("Connecting") {

}

void SyncTimePage::init() {
}

void SyncTimePage::draw(M5Display *lcd) {
    lcd->setCursor(4, 10);
    lcd->setTextSize(2);
    lcd->print("Sync Time");
    lcd->setTextSize(1);
    lcd->setCursor(4, 30);
    lcd->print("Wifi:");
    lcd->setCursor(40, 30);
    lcd->print(_wifiStatus);
}

void SyncTimePage::loadWidgets(WidgetManager *manager) {
    eventQueue.push(EVENT_WIFI_CONNECT, (uint32_t) 2 * 1000);
}

void SyncTimePage::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_WIFI_CONNECTED:
            _wifiStatus = "Connected";
            drawPage();
            eventQueue.push(EVENT_RTC_SYNC_TIME, (uint32_t) 2 * 1000);
        break;
        case EVENT_WIFI_DISCONNECTED:
            _wifiStatus = "Disconnected";
            drawPage();
        break;
        case EVENT_RTC_SYNC_TIME_DONE:
            _wifiStatus = "Sync completed";
            drawPage();
            eventQueue.push(EVENT_WIFI_DISCONNECT, (uint32_t) 2 * 1000);
        break;
    }
}
