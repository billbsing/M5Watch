#include "WifiManager.h"
#include "M5Watch.h"
#include "private.h"

WiFiManager::WiFiManager():
_isConnectedState(false) {

}


bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_WIFI_CONNECT:
            debug.print("WiFi: connect requested");
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        break;
        case EVENT_WIFI_DISCONNECT:
            debug.print("WiFi: disconnect requested");
            WiFi.disconnect();
        break;
    }
}

void WiFiManager::loop() {
    if ( isConnected() != _isConnectedState) {
        _isConnectedState = isConnected();
        if ( _isConnectedState) {
            eventQueue.push(EVENT_WIFI_CONNECTED);
        }
        else {
            eventQueue.push(EVENT_WIFI_DISCONNECTED);
        }
    }
}
