
#include "PageManager.h"
#include "Page.h"

PageManager::PageManager(M5StickC &m5, uint16_t width, uint16_t height):
_m5(m5),
_width(width),
_height(height),
_count(0),
_position(0) {
    memset(_pageList, 0, sizeof(Page *) * PAGE_MANGER_PAGE_LIST_SIZE);
}

void PageManager::init() {
    _nextPageWidget = TextWidget(PAGE_MANAGER_NEXT_PAGE_EVENT_ID, 30, 12, 4, 2, "Next");
    _nextPageWidget.setPosition(_width - _nextPageWidget.getWidth(), \
                                _height -  _nextPageWidget.getHeight());

    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE; index ++) {
        if ( _pageList[index] ) {
            _pageList[index]->init();
        }
    }
}

void PageManager::add(Page *page) {
    _pageList[_count] = page;
    _count ++;
    page->setIndex(_count);
}

void PageManager::next() {
    _position ++;
    if ( _position >= _count ) {
        _position = 0;
    }
}

uint8_t PageManager::getIndexFromName(String name) {
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE && index < _count; index ++) {
        if ( _pageList[index] ) {
            if ( _pageList[index]->getName() == name) {
                return index;
            }
        }
    }
    return _count + 1;
}

void PageManager::loadWidgets() {
    _widgetManager.clear();
    _pageList[_position]->loadWidgets(&_widgetManager);
    uint8_t index = _widgetManager.add(&_nextPageWidget);
    _widgetManager.setFocus(index);
}

void PageManager::draw() {
    _m5.Lcd.fillScreen(BLACK);
    if ( _pageList[_position]) {
        loadWidgets();
        _pageList[_position]->draw(_m5.Lcd);
    }
    _m5.Lcd.setCursor(_width - 80, _height - 10);
    _m5.Lcd.setTextSize(1);
    _m5.Lcd.printf("%d/%d", _position + 1, _count);

    _widgetManager.draw(_m5.Lcd);
}

void PageManager::processEvent(uint16_t eventId) {
    for ( uint8_t index = 0; index < PAGE_MANGER_PAGE_LIST_SIZE && index < _count; index ++) {
        if ( _pageList[index] ) {
            _pageList[index]->processEvent(eventId);
        }
    }
    if ( eventId ==  PAGE_MANAGER_NEXT_PAGE_EVENT_ID) {
        next();
        draw();
    }
}

void PageManager::selectPage(String name) {
    uint8_t index = getIndexFromName(name);
    if ( index < _count ) {
        setPosition(index);
        draw();
    }
}

void PageManager::loop() {
    uint16_t eventId;
    _m5.BtnB.read();
    if ( _m5.BtnB.isPressed() ) {
        _widgetManager.nextFocus(m5.Lcd);
    }
    M5.BtnA.read();
    if ( _m5.BtnA.isPressed() ) {
        _widgetManager.raiseEvent(_eventQueue);
    }
    eventId = _eventQueue.pop();
    if ( eventId ) {
        processEvent(eventId);
    }
}
