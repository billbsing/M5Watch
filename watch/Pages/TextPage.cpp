#include "TextPage.h"

TextPage::TextPage() {
    
}

void TextPage::init() {
}

void TextPage::begin() {
}

void TextPage::end() {
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
