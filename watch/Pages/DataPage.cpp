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
    _menuStart = TextWidget(getNextEventId(), x, y, \
                    MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, 4, 2, "Start");

    x += MENU_ITEM_WIDTH + MENU_ITEM_PADDING;
    _menuStop = TextWidget(getNextEventId(), x, y, \
                    MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, 4, 2, "Stop");

    x += MENU_ITEM_WIDTH + MENU_ITEM_PADDING;
    _menuUpload = TextWidget(getNextEventId(), x, y, \
                    MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, 4, 2, "Upload");
}

void DataPage::begin() {
}

void DataPage::end() {
}

void DataPage::loadWidgets(WidgetManager *manager) {
    manager->add(&_menuStart);
    manager->add(&_menuStop);
    manager->add(&_menuUpload);
}

void DataPage::draw(M5Display *lcd) {
    uint16_t y;
    lcd->setCursor(4, 0);
    lcd->setTextSize(0);
    lcd->print("Data Recorder");
    lcd->setTextSize(1);

    y = 10;
    lcd->setCursor(4, y);
    lcd->print("Gyro:");
    lcd->setCursor(45, y);
    lcd->printf("%+0.2f", dataRecorder.getGyro().x);
    lcd->setCursor(80, y);
    lcd->printf("%+0.2f", dataRecorder.getGyro().y);
    lcd->setCursor(120, y);
    lcd->printf("%+0.2f", dataRecorder.getGyro().z);

    y = 20;
    lcd->setCursor(4, y);
    lcd->print("Accel:");
    lcd->setCursor(45, y);
    lcd->printf("%+0.2f", dataRecorder.getAccel().x);
    lcd->setCursor(80, y);
    lcd->printf("%+0.2f", dataRecorder.getAccel().y);
    lcd->setCursor(120, y);
    lcd->printf("%+0.2f", dataRecorder.getAccel().z);

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
}

void DataPage::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_DATA_ON_CHANGE:
            drawPage();
        break;
    }
    if ( _menuStart.isEventId(eventId)) {
        eventQueue.push(EVENT_DATA_START);
    }
    if ( _menuStop.isEventId(eventId)) {
        eventQueue.push(EVENT_DATA_STOP);
    }
    if ( _menuUpload.isEventId(eventId)) {
        eventQueue.push(EVENT_DATA_UPLOAD);
    }

}
