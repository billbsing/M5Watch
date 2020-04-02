#include <TextWidget.h>
#include "DataPage.h"
#include "M5Watch.h"


DataPage::DataPage(PageManager *manager):
Page(manager) {
}

void DataPage::init() {
}

void DataPage::begin() {
}

void DataPage::end() {
}

void DataPage::loadWidgets(WidgetManager *manager) {
}

void DataPage::draw(M5Display *lcd) {
    uint16_t y;
    lcd->setCursor(4, 0);
    lcd->setTextSize(2);
    lcd->print("Data Recorder");
    lcd->setTextSize(1);

    y = 40;
    lcd->setCursor(0, y);
    lcd->print("Gyro");
    lcd->setCursor(40, y);
    lcd->printf("%0.2f", dataRecorder.getGyro().x);
    lcd->setCursor(80, y);
    lcd->printf("%0.2f", dataRecorder.getGyro().y);
    lcd->setCursor(120, y);
    lcd->printf("%0.2f", dataRecorder.getGyro().z);

    y = 80;
    lcd->setCursor(0, y);
    lcd->print("Accel");
    lcd->setCursor(40, y);
    lcd->printf("%0.2f", dataRecorder.getGyro().x);
    lcd->setCursor(80, y);
    lcd->printf("%0.2f", dataRecorder.getGyro().y);
    lcd->setCursor(120, y);
    lcd->printf("%0.2f", dataRecorder.getGyro().z);

}

void DataPage::processEvent(uint16_t eventId) {
    if ( eventId == EVENT_DATA_ON_CHANGE){
        // drawPage();
    }
}
