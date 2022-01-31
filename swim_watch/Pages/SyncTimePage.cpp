#include "SyncTimePage.h"
#include "M5Watch.h"

SyncTimePage::SyncTimePage():
_status("Wifi connecting") {
}

void SyncTimePage::init() {
}

void SyncTimePage::begin() {
}

void SyncTimePage::end() {
    eventQueue.remove(EVENT_RTC_SYNC_TIME);
    eventQueue.pushDelay(EVENT_WIFI_DISCONNECT, 1000);
}

void SyncTimePage::loadWidgets(WidgetManager *manager) {
    eventQueue.pushDelay(EVENT_WIFI_CONNECT, 2 * 1000);
}

void SyncTimePage::draw(M5Display *lcd) {
    drawHeader(lcd, "Sync Network Time");

    lcd->setTextSize(1);
    lcd->setCursor(4, 30);
    lcd->print(_status);
}

void SyncTimePage::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_WIFI_CONNECTED:
            _status = "Sync Time ";
            drawPage();
            _syncTimeCounter = 1;
            eventQueue.pushDelay(EVENT_RTC_SYNC_TIME, 1 * 1000);
        break;
        case EVENT_WIFI_DISCONNECTED:
            _status = "Finished";
            drawPage();
        break;
        case EVENT_RTC_SYNC_TIME:
            _status = "Sync Time ";
            for ( uint8_t i = 0; i < _syncTimeCounter; i ++) {
                _status += ".";
            }
            _syncTimeCounter ++;
            if ( _syncTimeCounter >= SYNC_TIME_PAGE_DOT_LENGTH ) {
                _syncTimeCounter = 1;
            }
            drawPage();
        break;
        case EVENT_RTC_SYNC_TIME_DONE:
            _status = "Sync completed";
            drawPage();
            eventQueue.pushDelay(EVENT_WIFI_DISCONNECT, 2 * 1000);
        break;
    }
}
