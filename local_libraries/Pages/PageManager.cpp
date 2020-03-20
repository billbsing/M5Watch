
#include <PageManager.h>
#include <Page.h>

PageManager::PageManager(M5StickC *m5, uint16_t width, uint16_t height):
_m5(m5),
_width(width),
_height(height),
_pageCount(0),
_stackCount(0),
_pageIndex(0),
_level(0) {
    memset(_pageList, 0, sizeof(PageItem) * PAGE_MANGER_PAGE_LIST_SIZE);
    memset(_callStack, 0, sizeof(uint8_t) * PAGE_MANAGER_CALL_STACK_SIZE);
}

void PageManager::build() {
    uint16_t left, top;
    left = _width - 30;
    top = _height -  12;
    _nextPageWidget = TextWidget(PAGE_MANAGER_NEXT_PAGE_EVENT_ID, left, top, 30, 12, 4, 2, "Next");
    _backPageWidget = TextWidget(PAGE_MANAGER_BACK_PAGE_EVENT_ID, left, top, 30, 12, 4, 2, "Back");
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE; index ++) {
        if ( _pageList[index].page ) {
            _pageList[index].page->init();
        }
    }
}

void PageManager::add(String name, Page *page, uint8_t level) {
    _pageList[_pageCount].name = name;
    _pageList[_pageCount].page = page;
    _pageList[_pageCount].level = level;
    _pageCount ++;
    page->setIndex(_pageCount);
}

void PageManager::next() {
    uint8_t index = _pageIndex;
    uint8_t counter = _pageCount + 1;
    while (counter > 0) {
        index ++;
        if ( index >= _pageCount || index >=  PAGE_MANGER_PAGE_LIST_SIZE) {
            index = 0;
        }
        if ( _pageList[index].level == _level) {
            setPageIndex(index);
            break;
        }
        counter --;
    }
}
uint8_t PageManager::getPageCountAtLevel(uint8_t level) {
    uint8_t counter = 0;
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE && index < _pageCount; index ++) {
        if ( _pageList[index].page && _pageList[index].level == level) {
            counter ++;
        }
    }
    return counter;
}
uint8_t PageManager::getPagePositionAtLevel(uint8_t position, uint8_t level) {
    uint8_t pagePosition = 0;
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE && index < _pageCount; index ++) {
        if ( _pageList[index].page && _pageList[index].level == level) {
            pagePosition ++;
            if ( index == position ){
                break;
            }
        }
    }
    return pagePosition;
}

uint8_t PageManager::getIndexFromName(String name) {
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE && index < _pageCount; index ++) {
        if ( _pageList[index].page ) {
            if ( _pageList[index].name == name) {
                return index;
            }
        }
    }
    return _pageCount + 1;
}

void PageManager::loadWidgets() {
    _widgetManager.clear();
    _pageList[_pageIndex].page->loadWidgets(&_widgetManager);

    // if there are > 1 pages on this level then just add a 'next' button
    if ( getPageCountAtLevel(_level) > 1 ) {
        uint8_t index = _widgetManager.add(&_nextPageWidget);
        _widgetManager.setFocus(index);
    }
    if ( _stackCount > 0 ) {
        uint8_t index = _widgetManager.add(&_backPageWidget);
        _widgetManager.setFocus(index);
    }
}

void PageManager::draw() {
    uint8_t pageCount = getPageCountAtLevel(_level);
    uint8_t pagePosition = getPagePositionAtLevel(_pageIndex, _level);
    _m5->Lcd.fillScreen(BLACK);
    if ( _pageList[_pageIndex].page) {
        loadWidgets();
        _pageList[_pageIndex].page->draw(&_m5->Lcd);
    }
    _m5->Lcd.setCursor(_width - 80, _height - 10);
    _m5->Lcd.setTextSize(1);
    _m5->Lcd.printf("%d/%d", pagePosition, pageCount);

    _widgetManager.draw(&_m5->Lcd);
}

void PageManager::processEvent(uint16_t eventId) {
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE && index < _pageCount; index ++) {
        if ( _pageList[index].page ) {
            _pageList[index].page->processEvent(eventId);
        }
    }
    if ( eventId ==  PAGE_MANAGER_NEXT_PAGE_EVENT_ID) {
        next();
        draw();
    }
    if ( eventId ==  PAGE_MANAGER_BACK_PAGE_EVENT_ID) {
        popPage();
        draw();
    }

}

void PageManager::selectPage(String name) {
    uint8_t index = getIndexFromName(name);
    if ( index < _pageCount ) {
        setPageIndex(index);
        draw();
    }
}

void PageManager::pushPage(String name) {
    uint8_t index = getIndexFromName(name);
    if ( index < _pageCount ) {
        pushCallStack(_pageIndex);
        setPageIndex(index);
        draw();
    }
}

void PageManager::popPage() {
    uint8_t index = popCallStack();
    if ( index < _pageCount ) {
        setPageIndex(index);
        draw();
    }
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

void PageManager::loop() {
    uint16_t eventId;
    _m5->BtnB.read();
    if ( _m5->BtnB.isPressed() ) {
        _widgetManager.nextFocus(&_m5->Lcd);
    }
    _m5->BtnA.read();
    if ( _m5->BtnA.isPressed() ) {
        _widgetManager.raiseEvent(&_eventQueue);
    }
    eventId = _eventQueue.pop();
    if ( eventId ) {
        processEvent(eventId);
    }
}
