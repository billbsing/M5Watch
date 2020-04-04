
#include <PageManager.h>
#include <Page.h>

PageManager::PageManager(M5StickC *m5, uint16_t width, uint16_t height, uint16_t startEventId):
_m5(m5),
_width(width),
_height(height),
_pageCount(0),
_lastPageIndex(PAGE_MANGER_PAGE_LIST_SIZE + 1),
_stackCount(0),
_pageIndex(0),
_pageGroup(0),
_eventIndex(startEventId) {
    memset(_pageList, 0, sizeof(PageItem) * PAGE_MANGER_PAGE_LIST_SIZE);
    memset(_callStack, 0, sizeof(uint8_t) * PAGE_MANAGER_CALL_STACK_SIZE);
}

void PageManager::build() {
    uint16_t left, top;
    left = _width - 30;
    top = _height -  12;
    _nextPageWidget = TextWidget(getNextEventId(), left, top, 30, 12, 4, 2, "Next");
    _backPageWidget = TextWidget(getNextEventId(), left, top, 30, 12, 4, 2, "Back");
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE; index ++) {
        if ( _pageList[index].page ) {
            _pageList[index].page->init();
        }
    }
}

void PageManager::add(uint8_t pageId, Page *page, uint8_t pageGroup) {
    _pageList[_pageCount].pageId = pageId;
    _pageList[_pageCount].page = page;
    _pageList[_pageCount].pageGroup = pageGroup;
    _pageCount ++;
    page->setIndex(_pageCount);
}

void PageManager::setPageIndex(uint8_t index) {
    if ( _pageList[index].page ) {
        _pageIndex = index;
        _pageGroup= _pageList[index].pageGroup;
    }
}

uint8_t PageManager::getPageCountInGroup(uint8_t pageGroup) {
    uint8_t counter = 0;
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE && index < _pageCount; index ++) {
        if ( _pageList[index].page && _pageList[index].pageGroup == pageGroup) {
            counter ++;
        }
    }
    return counter;
}
uint8_t PageManager::getPagePositionInGroup(uint8_t position, uint8_t pageGroup) {
    uint8_t pagePosition = 0;
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE && index < _pageCount; index ++) {
        if ( _pageList[index].page && _pageList[index].pageGroup == pageGroup) {
            pagePosition ++;
            if ( index == position ){
                break;
            }
        }
    }
    return pagePosition;
}

uint8_t PageManager::getIndexFromPageId(uint8_t pageId) {
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE && index < _pageCount; index ++) {
        if ( _pageList[index].page ) {
            if ( _pageList[index].pageId == pageId) {
                return index;
            }
        }
    }
    return _pageCount + 1;
}

void PageManager::loadWidgets() {
    _widgetManager.clear();
    _pageList[_pageIndex].page->loadWidgets(&_widgetManager);
//    _widgetManager.setFocus(false);

    bool isAddNext = false;
    // if there are > 1 pages on this pageGroup then just add a 'next' button
    if ( getPageCountInGroup(_pageGroup) > 1 ) {
        uint8_t index = _widgetManager.add(&_nextPageWidget);
//        _widgetManager.setFocus(index);
        isAddNext = true;
    }
    if ( _stackCount > 0 ) {
        _backPageWidget.setLeft(_nextPageWidget.getLeft());
        if ( isAddNext ) {
            _backPageWidget.setLeft(_nextPageWidget.getLeft() - _backPageWidget.getWidth() );
        }
        uint8_t index = _widgetManager.add(&_backPageWidget);
        if ( !isAddNext ) {
//            _widgetManager.setFocus(index);
        }
    }
    if ( _widgetManager.getFocusIndex() > _widgetManager.getCount() ) {
        _widgetManager.setFocus((uint8_t) _widgetManager.getCount() - 1);
    }
}

void PageManager::refresh() {
    loadPage();
    drawPage();
}

void PageManager::loadPage() {
    if ( _lastPageIndex < _pageCount ) {
        if ( _pageList[_lastPageIndex].page ) {
            _pageList[_lastPageIndex].page->end();
            _pageList[_lastPageIndex].page->setVisible(false);
        }
    }
    if ( _pageList[_pageIndex].page) {
        loadWidgets();
        _lastPageIndex = _pageIndex;
        _pageList[_pageIndex].page->setVisible(true);
        _pageList[_pageIndex].page->begin();
        _pageList[_pageIndex].page->draw(&_m5->Lcd);
    }
}

void PageManager::drawPage() {
    uint8_t pageCount = getPageCountInGroup(_pageGroup);
    uint8_t pagePosition = getPagePositionInGroup(_pageIndex, _pageGroup);
    _m5->Lcd.fillScreen(BLACK);
    if ( _pageList[_pageIndex].page) {
        _pageList[_pageIndex].page->draw(&_m5->Lcd);
    }
    _m5->Lcd.setCursor(_width - 80, _height - 10);
    _m5->Lcd.setTextSize(1);
    _m5->Lcd.printf("%d/%d", pagePosition, pageCount);
    _m5->Lcd.setTextSize(1);
    _widgetManager.draw(&_m5->Lcd);
}

uint16_t PageManager::getNextEventId() {
    _eventIndex++;
    return _eventIndex;
}

void PageManager::nextPage() {
    uint8_t index = _pageIndex;
    uint8_t counter = _pageCount + 1;
    while (counter > 0) {
        index ++;
        if ( index >= _pageCount || index >=  PAGE_MANGER_PAGE_LIST_SIZE) {
            index = 0;
        }
        if ( _pageList[index].pageGroup == _pageGroup) {
            setPageIndex(index);
            break;
        }
        counter --;
    }
    refresh();
}

void PageManager::selectPage(uint8_t pageId) {
    uint8_t index = getIndexFromPageId(pageId);
    if ( index < _pageCount ) {
        setPageIndex(index);
    }
    refresh();
}

void PageManager::pushPage(uint8_t pageId) {
    uint8_t index = getIndexFromPageId(pageId);
    if ( index < _pageCount && index != _pageIndex ) {
        pushCallStack(_pageIndex);
        setPageIndex(index);
    }
    refresh();
}

void PageManager::popPage() {
    uint8_t index = popCallStack();
    if ( index < _pageCount ) {
        setPageIndex(index);
    }
    refresh();
}

void PageManager::pushCallStack(uint8_t index) {
    if ( _stackCount < PAGE_MANAGER_CALL_STACK_SIZE ) {
        _callStack[_stackCount] = index;
        _stackCount ++;
    }
}

uint8_t PageManager::popCallStack() {
    uint8_t index = _pageCount + 1;
    if ( _stackCount > 0) {
        _stackCount --;
        index = _callStack[_stackCount];
    }
    return index;
}

void PageManager::rasieEventOnFocus(EventQueue *eventQueue) {
    _widgetManager.raiseEvent(eventQueue);
}
void PageManager::nextFocus() {
    _widgetManager.nextFocus(&_m5->Lcd);
}

void PageManager::processEvent(uint16_t eventId) {
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE && index < _pageCount; index ++) {
        if ( _pageList[index].page ) {
            _pageList[index].page->processEvent(eventId);
        }
    }
    if ( _nextPageWidget.isEventId(eventId) ) {
        nextPage();
    }
    if ( _backPageWidget.isEventId(eventId) ) {
        popPage();
    }
}
