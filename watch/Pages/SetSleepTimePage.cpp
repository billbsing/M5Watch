#include <TextWidget.h>
#include "SetSleepTimePage.h"
#include "M5Watch.h"

#define SET_SLEEP_TIME_PAGE_WIDGET_WIDTH            10
#define SET_SLEEP_TIME_PAGE_WIDGET_HEIGHT           12
#define SET_SLEEP_TIME_PAGE_WIDGET_PADDING          2

SetSleepTimePage::SetSleepTimePage(PageManager *manager):
Page(manager),
_value(0) {
}

void SetSleepTimePage::init() {
    uint16_t x = 100;
    uint16_t y = 25;
    _decrementWidget = TextWidget(getNextEventId(), x, y, \
                            SET_SLEEP_TIME_PAGE_WIDGET_WIDTH, \
                            SET_SLEEP_TIME_PAGE_WIDGET_HEIGHT, "^");
    y += SET_SLEEP_TIME_PAGE_WIDGET_HEIGHT + SET_SLEEP_TIME_PAGE_WIDGET_PADDING;
    _incrementWidget = TextWidget(getNextEventId(), x, y, \
                            SET_SLEEP_TIME_PAGE_WIDGET_WIDTH, \
                            SET_SLEEP_TIME_PAGE_WIDGET_HEIGHT, "v");
    _value = settings.getAutoPowerOffTimeout();
}

void SetSleepTimePage::draw(M5Display *lcd) {
    lcd->setCursor(4, 0);
    lcd->setTextSize(2);
    lcd->print("Sleep Time");
    lcd->setTextSize(1);
    lcd->setCursor(4, 35);
    lcd->print("Seconds:");
    lcd->setTextSize(2);
    lcd->setCursor(60, 30);
    lcd->printf("%d", _value);
}

void SetSleepTimePage::begin() {
}

void SetSleepTimePage::end() {
}

void SetSleepTimePage::loadWidgets(WidgetManager *manager) {
    manager->add(&_decrementWidget);
    manager->add(&_incrementWidget);
}

void SetSleepTimePage::processEvent(uint16_t eventId) {
    if ( _decrementWidget.isEventId(eventId)) {
        if ( _value > 0) {
            _value --;
            drawPage();
            settings.setAutoPowerOffTimeout(_value);
        }
    }

    if ( _incrementWidget.isEventId(eventId)) {
        _value ++;
        drawPage();
        settings.setAutoPowerOffTimeout(_value);
    }
}
