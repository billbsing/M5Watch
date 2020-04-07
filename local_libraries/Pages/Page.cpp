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
    StyleSheet styleSheet(_manager->getStyleSheet());

    uint16_t haaderHeight = styleSheet.getValue(STYLE_PAGE_HEADER_HEIGHT, 10);
    uint16_t textWidth = lcd->textWidth(title);
    lcd->fillRect(0, 0, \
            _manager->getWidth(), 10, \
            styleSheet.getValue(STYLE_PAGE_HEADER_BACKGROUND_COLOR, NAVY) \
    );
    lcd->setCursor((_manager->getWidth() - textWidth) / 2, 1);
    lcd->setTextSize(styleSheet.getValue(STYLE_PAGE_HEADER_FONT_SIZE, 1));
    lcd->setTextColor(styleSheet.getValue(STYLE_PAGE_HEADER_TEXT_COLOR, WHITE));
    lcd->print(title);
    lcd->setTextColor(styleSheet.getValue(STYLE_PAGE_DEFAULT_TEXT_COLOR, WHITE));
    lcd->setTextSize(styleSheet.getValue(STYLE_PAGE_DEFAULT_FONT_SIZE, 1));

}
