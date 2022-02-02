#include "WifiManager.h"
#include <SerialDebug.h>


WifiManager::WifiManager(uint16_t eventBaseId, const char *ssid, const char *password):
_eventBaseId(eventBaseId),
_ssid(ssid),
_password(password),
_isConnectedState(false) {

}


bool WifiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WifiManager::processEvent(uint16_t eventId) {
    int16_t wifiEvent = eventId - _eventBaseId;
    switch(wifiEvent) {
        case EVENT_WIFI_CONNECT_OFFSET:
            // debug.print("WiFi: connect requested");
            WiFi.begin(_ssid, _password);
        break;
        case EVENT_WIFI_DISCONNECT_OFFSET:
            // debug.print("WiFi: disconnect requested");
            WiFi.disconnect();
        break;
    }
}

void WifiManager::loop(EventQueue &eventQueue) {
    if ( isConnected() != _isConnectedState) {
        _isConnectedState = isConnected();
        if ( _isConnectedState) {
            eventQueue.push(_eventBaseId + EVENT_WIFI_CONNECTED_OFFSET);
        }
        else {
            eventQueue.push(_eventBaseId + EVENT_WIFI_DISCONNECTED_OFFSET);
        }
    }
}
