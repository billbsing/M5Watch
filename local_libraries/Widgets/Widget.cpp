#include "M5Watch.h"
#include <Widget.h>


Widget::Widget(uint16_t eventId, uint16_t left, uint16_t top, uint16_t width, uint16_t height):
_eventId(eventId),
_left(left),
_top(top),
_width(width),
_height(height),
_leftPadding(0),
_topPadding(0),
_isFocus(false) {
}

Widget::Widget(uint16_t eventId, uint16_t width, uint16_t height):
Widget(eventId, 0, 0, width, height) {

}

Widget::Widget():
Widget(0, 0, 0, 0, 0) {

}

Widget::Widget(const Widget &widget):
_left(widget.getLeft()),
_top(widget.getTop()),
_width(widget.getWidth()),
_height(widget.getHeight()),
_leftPadding(widget.getLeftPadding()),
_topPadding(widget.getTopPadding()),
_isFocus(widget.isFocus()),
_eventId(widget.getEventId()),
_styleSheet(widget.getStyleSheet()) {

}

void Widget::setCursor(M5Display *lcd) {
    lcd->setCursor(getLeft() + getLeftPadding(), getTop() + getTopPadding());
}

void Widget::showFocus(M5Display *lcd) {
    StyleSheet styleSheet(getStyleSheet());

    uint16_t color = styleSheet.getValue(STYLE_WIDGET_FOCUS_BORDER_COLOR, DARKGREY);
    if ( isFocus() ) {
        color = styleSheet.getValue(STYLE_WIDGET_BORDER_COLOR, WHITE);
    }
    lcd->drawRect(getLeft(), getTop(), getWidth(), getHeight(), color);
}

void Widget::raiseEvent(EventQueue *eventQueue) {
    if ( _eventId > 0) {
        eventQueue->push(_eventId);
    }
}
