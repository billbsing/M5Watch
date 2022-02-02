#include "TextWidget.h"

TextWidget::TextWidget(const TextWidget &textWidget):
Widget(textWidget),
_text(textWidget.getText()) {

}
TextWidget::TextWidget() {

}


void TextWidget::draw(M5Display *lcd) {
    uint16_t textWidth = lcd->textWidth(_text, 1);
    uint16_t fontHeight = lcd->fontHeight();
    lcd->setCursor(
        getLeft() + ((getWidth() - textWidth) / 2),
        getTop() + ((getHeight() - fontHeight) / 2)
    );
    lcd->print(_text);
}
