
#include <PageManager.h>
#include <Page.h>

PageManager::PageManager():
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
}

void PageManager::show(M5Display &lcd) {
    if ( _pageList[_position]) {
        _pageList[_position]->show(lcd);
    }
}
