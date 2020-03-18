// Widget List

#ifndef WIDGET_MANAGER_H
#define WIDGET_MANAGER_H

#include <Arduino.h>
#include <M5StickC.h>
#include "Widget.h"

#define WIDGET_MANAGER_LIST_SIZE            40

class WidgetManager
{
public:
    WidgetManager();

    void clear();
    void clear_and_delete();
    uint8_t add(Widget *widget);
    void show(M5Display &lcd);
    void setFocus(uint8_t index) { setFocus(index, true); }
    void setFocus(uint8_t index, bool value);
    void next();
    void raiseEvent();

protected:
    void showWidget(M5Display &lcd, Widget *widget);
    uint8_t getFocusIndex();

private:
    Widget *_widgetList[WIDGET_MANAGER_LIST_SIZE];
    uint8_t _count;
};

#endif              // WIDGET_MANAGER_H
