// WIFIManager

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <EventQueue.h>

#define EVENT_WIFI_CONNECT_OFFSET           0x00
#define EVENT_WIFI_DISCONNECT_OFFSET        0x01
#define EVENT_WIFI_CONNECTED_OFFSET         0x02
#define EVENT_WIFI_DISCONNECTED_OFFSET      0x03

class WifiManager
{

public:
    WifiManager(uint16_t eventBaseId, const char *ssid, const char *password);
    bool isConnected();
    void processEvent(uint16_t eventId);
    void loop(EventQueue &eventQueue);

private:
    uint16_t _eventBaseId;
    bool _isConnectedState;
    const char *_ssid;
    const char *_password;
};

#endif                  // WIFI_MANAGER_H
