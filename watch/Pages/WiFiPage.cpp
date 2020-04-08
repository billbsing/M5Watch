#include "WiFiPage.h"
#include "M5Watch.h"


#define MENU_ITEM_WIDTH                 75
#define MENU_ITEM_HEIGHT                12
#define MENU_ITEM_PADDING               2


WiFiPage::WiFiPage(PageManager *manager):
Page(manager),
_wifiStatus("Connecting") {
}


void WiFiPage::init() {

    uint16_t y = 12;
    uint16_t x = 4;
    _menuControl = TextWidget(getNextEventId(), x, y, \
                    MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, "Connect");

}

void WiFiPage::begin() {
    showStatus();
}

void WiFiPage::end() {
}

void WiFiPage::loadWidgets(WidgetManager *manager) {
    manager->add(&_menuControl);
}

void WiFiPage::draw(M5Display *lcd) {
    drawHeader(lcd, "WiFi");
    lcd->setTextSize(1);
}

void WiFiPage::processEvent(uint16_t eventId) {
    if (_menuControl.isEventId(eventId)) {
        if ( wifiManager.isConnected()) {
            eventQueue.pushDelay(EVENT_WIFI_DISCONNECT, 1 * 1000);
        }
        else {
            eventQueue.pushDelay(EVENT_WIFI_CONNECT, 1 * 1000);
        }
    }
    switch(eventId) {
        case EVENT_WIFI_CONNECTED:
            showStatus();
        break;
        case EVENT_WIFI_DISCONNECTED:
            showStatus();
        break;
    }
}

void WiFiPage::showStatus() {
    if ( wifiManager.isConnected()) {
        _menuControl.setText("Disconnect");
    }
    else {
        _menuControl.setText("Connect");
    }
}
