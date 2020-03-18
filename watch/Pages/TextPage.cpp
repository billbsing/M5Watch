#include "TextPage.h"

void TextPage::show(M5Display &lcd) {
    lcd.setCursor(4, 10);
    lcd.setTextSize(2);
    lcd.print(_text);
}

void TextPage::loadWidgets(WidgetManager *manager)
{

}
