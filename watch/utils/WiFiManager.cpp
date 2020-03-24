#include "WiFiManager.h"
#include "M5Watch.h"
#include "private.h"


bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::processEvent(uint16_t eventId) {
    if ( eventId == EVENT_WIFI_CONNECT) {
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }
}

void WiFiManager::loop() {
    if ( isConnected() != _isConnected) {
        _isConnected = isConnected();
        if ( _isConnected) {
            eventQueue.push(EVENT_WIFI_CONNECTED);
        }
        else {
            eventQueue.push(EVENT_WIFI_DISCONNECTED);
        }
    }
}
