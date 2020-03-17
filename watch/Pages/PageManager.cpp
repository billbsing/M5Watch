
#include <PageManager.h>
#include <Page.h>

PageManager::PageManager(uint16_t width, uint16_t height):
_width(width),
_height(height),
_count(0),
_position(0) {
    memset(_pageList, 0, sizeof(void *) * PAGE_MANGER_PAGE_LIST_SIZE);
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
    show();
}

void PageManager::show() {
    _lcd->fillScreen(BLACK);
    if ( _pageList[_position]) {
        _pageList[_position]->show(_lcd);
    }
    _lcd->setCursor(_width - 20, _height - 10);
    _lcd->setTextSize(1);
    _lcd->printf("%d/%d", _position + 1, _count);
}
