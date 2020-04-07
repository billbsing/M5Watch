#include <TextWidget.h>
#include "DataPage.h"
#include "M5Watch.h"

#define MENU_ITEM_WIDTH                 45
#define MENU_ITEM_HEIGHT                12
#define MENU_ITEM_PADDING               5


DataPage::DataPage(PageManager *manager):
Page(manager) {
}

void DataPage::init() {
    uint16_t y = 52;
    uint16_t x = 4;
    _menuStartStop = TextWidget(getNextEventId(), x, y, \
                    MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, "Start");

    x += MENU_ITEM_WIDTH + MENU_ITEM_PADDING;
    _menuUpload = TextWidget(getNextEventId(), x, y, \
                    MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, "Upload");

    x += MENU_ITEM_WIDTH + MENU_ITEM_PADDING;
    _menuDelete = TextWidget(getNextEventId(), x, y, \
                    MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, "Delete");
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
    lcd->setCursor(50, y);
    lcd->printf("Count: %ld", dataRecorder.getStoreCount());
}

void DataPage::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_DATA_ON_CHANGE:
            drawPage();
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
        eventQueue.push(EVENT_DATA_UPLOAD);
    }
    if ( _menuDelete.isEventId(eventId)) {
        eventQueue.push(EVENT_DATA_DELETE);
    }

}
