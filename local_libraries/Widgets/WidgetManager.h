// Widget List

#ifndef WIDGET_MANAGER_H
#define WIDGET_MANAGER_H

#include <Arduino.h>
#include <M5StickC.h>
#include <EventQueue.h>
#include <Widget.h>

#define WIDGET_MANAGER_LIST_SIZE            40

class WidgetManager
{
public:
    WidgetManager();

    void clear();
    void clear_and_delete();
    uint8_t add(Widget *widget);
    void draw(M5Display *lcd);
    void setFocus(uint8_t index) { setFocus(index, true); }
    void setFocus(uint8_t index, bool value);
    void nextFocus(M5Display *lcd);
    void raiseEvent(EventQueue *eventQueue);

protected:
    void drawWidget(M5Display *lcd, Widget *widget);
    uint8_t getFocusIndex();

private:
    Widget *_widgetList[WIDGET_MANAGER_LIST_SIZE];
    uint8_t _count;
};

#endif              // WIDGET_MANAGER_H
