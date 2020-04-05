#include <TextWidget.h>

TextWidget::TextWidget(uint16_t eventId, uint16_t left, uint16_t top, uint16_t width, uint16_t height, String text):
Widget(eventId, left, top, width, height),
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
