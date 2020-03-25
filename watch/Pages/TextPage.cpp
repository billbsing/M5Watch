#include "TextPage.h"

TextPage::TextPage(PageManager *manager, String text):
Page(manager),
_text(text) {
}

void TextPage::init() {
}

void TextPage::begin() {
}

void TextPage::loadWidgets(WidgetManager *manager) {
}

void TextPage::draw(M5Display *lcd) {
    lcd->setCursor(4, 10);
    lcd->setTextSize(2);
    lcd->print(_text);
}

void TextPage::processEvent(uint16_t eventId) {
}
