#include "TextWidget.h"

TextWidget::TextWidget(uint16_t width, uint16_t height, String text):
Widget(width, height),
_text(text) {

}

TextWidget::TextWidget(uint16_t width, uint16_t height, uint16_t leftPadding, uint16_t topPadding, String text):
Widget(width, height, leftPadding, topPadding),
_text(text) {

}

void TextWidget::show(M5Display *lcd) {
    lcd->drawRect(getLeft(), getTop(), getWidth(), getHeight(), WHITE);
    lcd->setCursor(getLeft() + getLeftPadding(), getTop() + getTopPadding());
    lcd->print(_text);
}
