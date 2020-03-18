#include "Widget.h"

Widget::Widget(uint16_t left, uint16_t top, uint16_t width, uint16_t height, uint8_t leftPadding, uint8_t topPadding):
_left(left),
_top(top),
_width(width),
_height(height),
_leftPadding(leftPadding),
_topPadding(topPadding) {
}

Widget::Widget(uint16_t width, uint16_t height, uint8_t leftPadding, uint8_t topPadding):
_left(0),
_top(0),
_width(width),
_height(height),
_leftPadding(leftPadding),
_topPadding(topPadding) {
}

Widget::Widget(uint16_t width, uint16_t height):
_left(0),
_top(0),
_width(width),
_height(height),
_leftPadding(1),
_topPadding(1) {
}
