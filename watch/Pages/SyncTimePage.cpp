#include "SyncTimePage.h"
#include "M5Watch.h"

SyncTimePage::SyncTimePage(PageManager *manager):
Page(manager),
_wifiStatus("connecting") {

}

void SyncTimePage::init() {
    eventQueue.push(EVENT_WIFI_CONNECT);
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

}

void SyncTimePage::processEvent(uint16_t eventId) {
    if ( eventId == EVENT_WIFI_CONNECTED) {
        _wifiStatus = "connected";
        drawPage();
    }
    if ( eventId == EVENT_WIFI_DISCONNECTED) {
        _wifiStatus = "disconnected";
        drawPage();
    }
}
