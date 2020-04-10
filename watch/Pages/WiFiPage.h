// WiFiPage

#ifndef WIFI_PAGE_H
#define WIFI_PAGE_H


#include <Page.h>
#include <TextWidget.h>

class WiFiPage: public Page
{
public:
    WiFiPage();

    void init();
    void begin();
    void end();
    void loadWidgets(WidgetManager *manager);
    void draw(M5Display *lcd);
    void processEvent(uint16_t eventId);

protected:
    void showStatus();

private:
    String _wifiStatus;
    TextWidget _menuControl;

};


#endif          // WIFI_PAGE_H
