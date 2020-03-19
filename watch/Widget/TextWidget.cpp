#include "TextWidget.h"

TextWidget::TextWidget(uint16_t eventId, uint16_t left, uint16_t top, uint16_t width, uint16_t height, uint16_t leftPadding, uint16_t topPadding, String text):
Widget(eventId, left, top, leftPadding, topPadding),
_text(text) {

}

TextWidget::TextWidget(uint16_t eventId, uint16_t width, uint16_t height, uint16_t leftPadding, uint16_t topPadding, String text):
Widget(eventId, width, height, leftPadding, topPadding),
_text(text) {

}

TextWidget::TextWidget(uint16_t eventId, uint16_t width, uint16_t height, String text):
Widget(eventId, width, height),
_text(text) {

}
TextWidget::TextWidget(const TextWidget &textWidget):
Widget(textWidget),
_text(textWidget.getText()) {

}

void TextWidget::draw(M5Display &lcd) {
    lcd.print(_text);
}
