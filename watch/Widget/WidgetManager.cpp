#include "WidgetManager.h"



WidgetManager::WidgetManager():
_count(0) {
    clear();
}

void WidgetManager::clear() {
    memset(_widgetList, 0, sizeof(Widget *) * WIDGET_MANAGER_LIST_SIZE);
    _count = 0;
}

void WidgetManager::clear_and_delete() {
    for ( uint8_t index = 0; index < _count; index ++) {
        delete _widgetList[index];
        _widgetList[index] = NULL;
    }
    clear();
}

uint8_t WidgetManager::add(Widget *widget) {
    uint8_t index = _count;
    if (_count < WIDGET_MANAGER_LIST_SIZE) {
        _widgetList[_count] = widget;
        _count ++;
    }
    return index;
}

void WidgetManager::showWidget(M5Display &lcd, Widget *widget) {
    widget->showFocus(lcd);
    widget->setCursor(lcd);
    widget->show(lcd);
}


void WidgetManager::show(M5Display &lcd) {
    for ( uint8_t index = 0; index < _count ; index ++) {
        if ( _widgetList[index] ) {
            showWidget(lcd, _widgetList[index]);
        }
    }
}

void WidgetManager::setFocus(uint8_t index, bool value) {
    if ( _widgetList[index] ) {
        _widgetList[index]->setFocus(true);
    }
}

uint8_t WidgetManager::getFocusIndex() {
    uint8_t focusIndex = _count + 1;
    for ( uint8_t index = 0; index < _count ; index ++) {
        if ( _widgetList[index] ) {
            if ( _widgetList[index]->isFocus()) {
                focusIndex = index;
                break;
            }
        }
    }
    return focusIndex;
}

void WidgetManager::next() {
    uint8_t index = getFocusIndex();
    uint8_t lastIndex = index;
    index ++;
    if ( index >= _count ) {
        index = 0;
    }
    if ( lastIndex != index) {
        setFocus(lastIndex, false);
        setFocus(index, true);
    }
}

void WidgetManager::raiseEvent() {
    uint8_t index = getFocusIndex();
    if ( index < _count ) {
    }
}
