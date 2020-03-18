
#include "PageManager.h"
#include "Page.h"
#include "TextWidget.h"

PageManager::PageManager(uint16_t width, uint16_t height):
_width(width),
_height(height),
_count(0),
_position(0),
_nextPageWidget(30, 12, 4, 2, "Next") {
    memset(_pageList, 0, sizeof(Page *) * PAGE_MANGER_PAGE_LIST_SIZE);
    _nextPageWidget.setPosition(_width - _nextPageWidget.getWidth(), _height -  _nextPageWidget.getHeight());
}
void PageManager::add(Page *page) {
    _pageList[_count] = page;
    _count ++;
}

void PageManager::next() {
    _position ++;
    if ( _position >= _count ) {
        _position = 0;
    }
}

void PageManager::show(M5Display *lcd) {
    lcd->fillScreen(BLACK);
    if ( _pageList[_position]) {
        _pageList[_position]->show(lcd);
    }
    lcd->setCursor(_width - 80, _height - 10);
    lcd->setTextSize(1);
    lcd->printf("%d/%d", _position + 1, _count);

    _nextPageWidget.show(lcd);
}
