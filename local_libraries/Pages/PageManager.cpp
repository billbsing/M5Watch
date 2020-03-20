
#include <PageManager.h>
#include <Page.h>

PageManager::PageManager(M5StickC *m5, uint16_t width, uint16_t height):
_m5(m5),
_width(width),
_height(height),
_pageCount(0),
_stackCount(0),
_pageIndex(0),
_level(0),
_buttonsEnabled({true, true}) {
    memset(_pageList, 0, sizeof(PageItem) * PAGE_MANGER_PAGE_LIST_SIZE);
    memset(_callStack, 0, sizeof(uint8_t) * PAGE_MANAGER_CALL_STACK_SIZE);
}

void PageManager::build() {
    uint16_t left, top;
    left = _width - 30;
    top = _height -  12;
    _nextPageWidget = TextWidget(EVENT_NEXT_PAGE, left, top, 30, 12, 4, 2, "Next");
    _backPageWidget = TextWidget(EVENT_BACK_PAGE, left, top, 30, 12, 4, 2, "Back");
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE; index ++) {
        if ( _pageList[index].page ) {
            _pageList[index].page->init();
        }
    }
}

void PageManager::add(uint8_t pageId, Page *page, uint8_t level) {
    _pageList[_pageCount].pageId = pageId;
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

void PageManager::setPageIndex(uint8_t index) {
    _pageIndex = index;
    if ( _pageList[index].page ) {
        _level = _pageList[index].level;
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
    _widgetManager.setFocus(false);

    bool isAddNext = false;
    // if there are > 1 pages on this level then just add a 'next' button
    if ( getPageCountAtLevel(_level) > 1 ) {
        uint8_t index = _widgetManager.add(&_nextPageWidget);
        _widgetManager.setFocus(index);
        isAddNext = true;
    }
    if ( _stackCount > 0 ) {
        _backPageWidget.setLeft(_nextPageWidget.getLeft());
        if ( isAddNext ) {
            _backPageWidget.setLeft(_nextPageWidget.getLeft() - _backPageWidget.getWidth() );
        }
        uint8_t index = _widgetManager.add(&_backPageWidget);
        if ( !isAddNext ) {
            _widgetManager.setFocus(index);
        }
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


void PageManager::selectPage(uint8_t pageId) {
    uint8_t index = getIndexFromPageId(pageId);
    if ( index < _pageCount ) {
        setPageIndex(index);
        draw();
    }
}

void PageManager::pushPage(uint8_t pageId) {
    uint8_t index = getIndexFromPageId(pageId);
    if ( index < _pageCount && index != _pageIndex ) {
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
    Serial.print("pop stack ");
    if ( _stackCount > 0) {
        _stackCount --;
        index = _callStack[_stackCount];
        Serial.print(_stackCount);
        Serial.print(" ");
    }
    Serial.println(index);
    return index;
}

void PageManager::processEvent(uint16_t eventId) {
    Serial.print("eventId ");
    Serial.println(eventId);
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE && index < _pageCount; index ++) {
        if ( _pageList[index].page ) {
            _pageList[index].page->processEvent(eventId);
        }
    }
    switch(eventId) {
        case EVENT_NEXT_PAGE:
            next();
            draw();
            break;
        case EVENT_BACK_PAGE:
            Serial.println("Page back");
            popPage();
            draw();
            break;
    }
}

void PageManager::loop() {
    uint16_t eventId;
    _m5->BtnB.read();
    _m5->BtnA.read();
    if ( _buttonsEnabled.buttonA ) {
        if ( _m5->BtnA.isPressed() ) {
            _buttonsEnabled.buttonA = false;
            _widgetManager.raiseEvent(&_eventQueue);
        }
    }
    if ( _m5->BtnA.isReleased() ) {
        _buttonsEnabled.buttonA = true;
    }
    if ( _buttonsEnabled.buttonB ) {
        if ( _m5->BtnB.isPressed() ) {
            _buttonsEnabled.buttonB = false;
            _widgetManager.nextFocus(&_m5->Lcd);
        }
    }
    if ( _m5->BtnB.isReleased() ) {
        _buttonsEnabled.buttonB = true;
    }
    eventId = _eventQueue.pop();
    if ( eventId ) {
        processEvent(eventId);
    }
}
