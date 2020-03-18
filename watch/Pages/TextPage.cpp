#include "TextPage.h"

void TextPage::show(M5Display &lcd) {
    lcd.setCursor(4, 10);
    lcd.setTextSize(2);
    lcd.print(_text);
}

void TextPage::loadWidgets(WidgetManager *manager) {

}

void TextPage::processEvent(uint16_t eventId) {

}
