// WIFIManager

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

class WiFiManager
{

public:
    WiFiManager();

    bool isConnected();
    void processEvent(uint16_t eventId);
    void loop();

private:
    bool _isConnectedState;
};

#endif                  // WIFI_MANAGER_H
