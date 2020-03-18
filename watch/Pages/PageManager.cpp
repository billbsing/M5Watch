
#include "PageManager.h"
#include "Page.h"
#include "TextWidget.h"

PageManager::PageManager(uint16_t width, uint16_t height):
_width(width),
_height(height),
_count(0),
_position(0) {
    memset(_pageList, 0, sizeof(Page *) * PAGE_MANGER_PAGE_LIST_SIZE);
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

void PageManager::loadWidgets() {
    _widgetManager.clear_and_delete();
    _pageList[_position]->loadWidgets(&_widgetManager);
    TextWidget *nextPageWidget = new TextWidget(30, 12, 4, 2, "Next");
    nextPageWidget->setPosition(_width - nextPageWidget->getWidth(), _height -  nextPageWidget->getHeight());
    uint8_t index = _widgetManager.add(nextPageWidget);
    _widgetManager.setFocus(index);
}

void PageManager::show(M5Display &lcd) {
    lcd.fillScreen(BLACK);
    if ( _pageList[_position]) {
        loadWidgets();
        _pageList[_position]->show(lcd);
    }
    lcd.setCursor(_width - 80, _height - 10);
    lcd.setTextSize(1);
    lcd.printf("%d/%d", _position + 1, _count);

    _widgetManager.show(lcd);
}

void PageManager::loop(M5StickC &m5) {
    m5.BtnB.read();
    if ( m5.BtnB.isPressed() ) {
        _widgetManager.next();
        _widgetManager.show(m5.Lcd);
    }
    M5.BtnA.read();
    if ( m5.BtnA.isPressed() ) {
        _widgetManager.raiseEvent();
    }
}
