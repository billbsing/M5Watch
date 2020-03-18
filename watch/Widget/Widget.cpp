#include "Widget.h"

Widget::Widget(uint16_t eventId, uint16_t left, uint16_t top, uint16_t width, uint16_t height, uint8_t leftPadding, uint8_t topPadding):
_eventId(eventId) ,
_left(left),
_top(top),
_width(width),
_height(height),
_leftPadding(leftPadding),
_topPadding(topPadding),
_isFocus(false) {
}

Widget::Widget(uint16_t eventId, uint16_t width, uint16_t height, uint8_t leftPadding, uint8_t topPadding):
Widget(eventId, 0, 0, width, height, leftPadding, topPadding) {
}

Widget::Widget(uint16_t eventId, uint16_t width, uint16_t height):
Widget(eventId, 0, 0, width, height, 1, 1) {
}

void Widget::setCursor(M5Display &lcd) {
    lcd.setCursor(getLeft() + getLeftPadding(), getTop() + getTopPadding());
}

void Widget::showFocus(M5Display &lcd) {
    uint16_t color = BLACK;
    if ( isFocus() ) {
        color = WHITE;
    }
    lcd.drawRect(getLeft(), getTop(), getWidth(), getHeight(), WHITE);
}

void Widget::raiseEvent(EventQueue &eventQueue) {
    eventQueue.push(_eventId);
}
