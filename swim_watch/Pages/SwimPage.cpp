#include "M5Watch.h"
#include "SwimPage.h"

#define MENU_ITEM_WIDTH                 45
#define MENU_ITEM_HEIGHT                12
#define MENU_ITEM_PADDING               5

SwimPage::SwimPage():
_vibratorMotor(VIBRATOR_MOTOR_PIN) {

}

void SwimPage::init() {
    uint16_t y = 52;
    uint16_t x = 4;
    _menuStartStop.setPosition(x, y);
    _menuStartStop.setSize(MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT);
    _menuStartStop.setText("Start");
}

void SwimPage::draw(M5Display *lcd) {
    drawHeader(lcd, "Swim Timer");
}

void SwimPage::begin() {
    _vibratorMotor.begin();
}

void SwimPage::end() {
}

void SwimPage::loadWidgets(WidgetManager *manager) {
    manager->add(&_menuStartStop);
}

void SwimPage::processEvent(uint16_t eventId) {
    _vibratorMotor.processEvent(eventId);
    if ( _menuStartStop.isEventId(eventId)) {
        _vibratorMotor.signal(2);
    }
}
