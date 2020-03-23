#include <WidgetManager.h>



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

void WidgetManager::drawWidget(M5Display *lcd, Widget *widget) {
    if ( widget ) {
        widget->showFocus(lcd);
        widget->setCursor(lcd);
        widget->draw(lcd);
    }
}


void WidgetManager::draw(M5Display *lcd) {
    for ( uint8_t index = 0; index < _count && index < WIDGET_MANAGER_LIST_SIZE; index ++) {
        if ( _widgetList[index] ) {
            drawWidget(lcd, _widgetList[index]);
        }
    }
}

void WidgetManager::setFocusAll(bool value) {
    for ( uint8_t index = 0; index < _count && index < WIDGET_MANAGER_LIST_SIZE ; index ++) {
        if ( _widgetList[index] ) {
            setFocus(index, value);
        }
    }
}

void WidgetManager::setFocus(uint8_t index, bool value) {
    if ( _widgetList[index] ) {
        _widgetList[index]->setFocus(value);
    }
}

uint8_t WidgetManager::getFocusIndex() {
    uint8_t focusIndex = _count + 1;
    for ( uint8_t index = 0; index < _count && index < WIDGET_MANAGER_LIST_SIZE ; index ++) {
        if ( _widgetList[index] ) {
            if ( _widgetList[index]->isFocus()) {
                focusIndex = index;
                break;
            }
        }
    }
    return focusIndex;
}

void WidgetManager::nextFocus(M5Display *lcd) {
    uint8_t index = getFocusIndex();
    uint8_t lastIndex = index;
    index ++;
    if ( index >= _count ) {
        index = 0;
    }
    if ( lastIndex != index) {
        setFocus(lastIndex, false);
        drawWidget(lcd, _widgetList[lastIndex]);
        setFocus(index, true);
        drawWidget(lcd, _widgetList[index]);
    }
}

void WidgetManager::raiseEvent(EventQueue *eventQueue) {
    uint8_t index = getFocusIndex();
    if ( index < _count ) {
        if ( _widgetList[index]) {
            _widgetList[index]->raiseEvent(eventQueue);
        }
    }
}
