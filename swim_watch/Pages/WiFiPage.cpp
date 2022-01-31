#include "WiFiPage.h"
#include "M5Watch.h"


#define MENU_ITEM_WIDTH                 75
#define MENU_ITEM_HEIGHT                12
#define MENU_ITEM_PADDING               2


WiFiPage::WiFiPage():
_wifiStatus("Connecting") {

}


void WiFiPage::init() {

    uint16_t y = getManager()->getHeight() - 22;
    uint16_t x = 4;
    _menuControl.setPosition(x, y);
    _menuControl.setSize(MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT);
    _menuControl.setText("Connect");

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
    uint16_t y = getHeaderHeight() + 2;
    drawHeader(lcd, "WiFi");
    lcd->setTextSize(1);
    lcd->setCursor(4, y);
    lcd->printf("IP: %s", WiFi.localIP().toString().c_str());
    y += 10;
    lcd->setCursor(4, y);
    lcd->printf("Subnet: %s", WiFi.subnetMask().toString().c_str());
    y += 10;
    lcd->setCursor(4, y);
    lcd->printf("Gateway: %s", WiFi.gatewayIP().toString().c_str());
    y += 10;
    lcd->setCursor(4, y);
    if ( WiFi.getHostname() ) {
        lcd->printf("Hostname: %s", WiFi.getHostname());
    }
    else {
        lcd->print("Hostname:");
    }
}

void WiFiPage::processEvent(uint16_t eventId) {
    if (_menuControl.isEventId(eventId)) {
        if ( wifiManager.isConnected()) {
            debug.print("send disconnect");
            eventQueue.pushDelay(EVENT_WIFI_DISCONNECT, 2 * 1000);
            _menuControl.setText("Disconnecting");
            drawPage();
        }
        else {
            debug.print("send connect");
            eventQueue.pushDelay(EVENT_WIFI_CONNECT, 2 * 1000);
            _menuControl.setText("Connecting");
            drawPage();
        }
    }
    switch(eventId) {
        case EVENT_WIFI_CONNECTED:
            showStatus();
            drawPage();
        break;
        case EVENT_WIFI_DISCONNECTED:
            showStatus();
            drawPage();
        break;
    }
}

void WiFiPage::showStatus() {
    if ( wifiManager.isConnected()) {
        debug.print("wifi connected");
        _menuControl.setText("Disconnect");
    }
    else {
        debug.print("wifi disconnected");
        _menuControl.setText("Connect");
    }
}
