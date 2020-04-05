#include <Page.h>
#include <PageManager.h>

Page::Page(PageManager *manager):
_manager(manager),
_index(0),
_isVisible(false) {

}

void Page::drawPage() {
    if (_isVisible) {
        _manager->drawPage();
    }
}

void Page::drawHeader(M5Display *lcd, String title) {
    uint16_t textWidth = lcd->textWidth(title);
    lcd->fillRect(0, 0, _manager->getWidth(), 10, NAVY);
    lcd->setCursor((_manager->getWidth() - textWidth) / 2, 1);
    lcd->setTextSize(1);
    lcd->setTextColor(WHITE);
    lcd->print(title);
    lcd->setTextColor(WHITE);

}
