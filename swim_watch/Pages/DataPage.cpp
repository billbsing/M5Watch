#include <TextWidget.h>
#include "DataPage.h"
#include "M5Watch.h"

#define MENU_ITEM_WIDTH                 45
#define MENU_ITEM_HEIGHT                12
#define MENU_ITEM_PADDING               5


DataPage::DataPage() {
    _isWaitForConnection = false;
}

void DataPage::init() {
    uint16_t y = 52;
    uint16_t x = 4;
    _menuStartStop.setPosition(x, y);
    _menuStartStop.setSize(MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT);
    _menuStartStop.setText("Start");

    x += MENU_ITEM_WIDTH + MENU_ITEM_PADDING;
    _menuUpload.setPosition(x, y);
    _menuUpload.setSize(MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT);
    _menuUpload.setText("Upload");

    x += MENU_ITEM_WIDTH + MENU_ITEM_PADDING;
    _menuDelete.setPosition(x, y);
    _menuDelete.setSize(MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT);
    _menuDelete.setText("Delete");
}

void DataPage::begin() {
    eventQueue.push(EVENT_DATA_INIT);
}

void DataPage::end() {
}

void DataPage::loadWidgets(WidgetManager *manager) {
    manager->add(&_menuStartStop);
    manager->add(&_menuUpload);
    manager->add(&_menuDelete);
}

void DataPage::draw(M5Display *lcd) {
    uint16_t y;
    drawHeader(lcd, "Data Recorder");

    lcd->setTextSize(1);
    y = getHeaderHeight() + 2;
    lcd->setCursor(4, y);
    lcd->print("Gyro:");
    lcd->setCursor(42, y);
    lcd->printf("%+0.2f", dataRecorder.getGyro().getX());
    lcd->setCursor(82, y);
    lcd->printf("%+0.2f", dataRecorder.getGyro().getY());
    lcd->setCursor(124, y);
    lcd->printf("%+0.2f", dataRecorder.getGyro().getZ());

    y = 20;
    lcd->setCursor(4, y);
    lcd->print("Accel:");
    lcd->setCursor(42, y);
    lcd->printf("%+0.2f", dataRecorder.getAccel().getX());
    lcd->setCursor(82, y);
    lcd->printf("%+0.2f", dataRecorder.getAccel().getY());
    lcd->setCursor(124, y);
    lcd->printf("%+0.2f", dataRecorder.getAccel().getZ());

    y = 30;
    lcd->setCursor(4, y);
    DataStoreHeader header = dataRecorder.getStoreHeader();
    lcd->printf("Count:%ld", header.getStoreCount());
    lcd->setCursor(60, y);
    lcd->printf("Upload:%ld", header.getUploadCount());

    y = 40;
    lcd->setCursor(4, y);
    switch(dataRecorder.getStatus()) {
        case dataIdle:
            lcd->print("Idle");
        break;
        case dataRecord:
            lcd->print("Record");
        break;
        case dataUpload:
            lcd->print("Upload");
        break;
    }

}

void DataPage::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_DATA_ON_CHANGE:
            drawPage();
        break;
        case EVENT_WIFI_CONNECTED:
            if ( _isWaitForConnection ) {
                eventQueue.push(EVENT_DATA_UPLOAD);
                _menuUpload.setText("Cancel");
                _isWaitForConnection = false;
            }
        break;
    }
    if ( _menuStartStop.isEventId(eventId)) {
        if ( dataRecorder.getStatus() == dataIdle ) {
            eventQueue.push(EVENT_DATA_START);
            _menuStartStop.setText("Stop");
        }
        if ( dataRecorder.getStatus() == dataRecord ) {
            eventQueue.push(EVENT_DATA_STOP);
            _menuStartStop.setText("Start");
        }
    }
    if ( _menuUpload.isEventId(eventId)) {
        if ( dataRecorder.getStatus() == dataUpload ) {
            eventQueue.push(EVENT_DATA_UPLOAD_CANCEL);
            _menuUpload.setText("Upload");
            if ( wifiManager.isConnected()) {
                eventQueue.pushDelay(EVENT_WIFI_DISCONNECT, 500);
            }
        }
        else {
            if ( !wifiManager.isConnected()) {
                eventQueue.pushDelay(EVENT_WIFI_CONNECT, 500);
                _menuUpload.setText("Connect");
                _isWaitForConnection = true;
            }
            else {
                eventQueue.push(EVENT_DATA_UPLOAD);
                _menuUpload.setText("Cancel");
            }
        }
    }
    if ( _menuDelete.isEventId(eventId)) {
        eventQueue.push(EVENT_DATA_DELETE);
    }

}
