// Widget Base Class

#ifndef WIDGET_H
#define WIDGET_H

#include <Arduino.h>
#include <M5StickC.h>
#include <EventQueue.h>
#include <WidgetStyle.h>

class Widget
{
public:
    Widget(uint16_t eventId, uint16_t left, uint16_t top, uint16_t width, uint16_t height);
    Widget(uint16_t eventId, uint16_t width, uint16_t height);
    Widget();
    Widget(const Widget &widget);

    virtual void draw(M5Display *lcd) = 0;
    void showFocus(M5Display *lcd);
    void setCursor(M5Display *lcd);

    void setLeft(uint16_t value) { _left = value; }
    void setTop(uint16_t value) { _top = value; }
    void setPosition(uint16_t left, uint16_t top) { _left = left; _top = top; }
    uint16_t getLeft() const { return _left; }
    uint16_t getTop() const { return _top; }

    void setWidth(uint16_t value) { _width = value; }
    void setHeight(uint16_t value) { _height = value; }
    void setSize(uint16_t width, uint16_t height) { _width = width; _height = height; }
    uint16_t getWidth() const { return _width; }
    uint16_t getHeight() const { return _height; }

    void setLeftPadding(uint8_t value) { _leftPadding = value; }
    void setTopPadding(uint8_t value) { _topPadding = value; }
    void setPadding(uint8_t leftPadding, uint8_t topPadding) { _leftPadding = leftPadding; _topPadding = topPadding; }
    uint8_t getLeftPadding() const { return _leftPadding; }
    uint8_t getTopPadding() const { return _topPadding; }

    void setFocus(bool value) { _isFocus = value; }
    bool isFocus() const { return _isFocus; }

    void setEventId(uint16_t value) { _eventId = value; }
    bool isEventId(uint16_t value) const { return _eventId == value; }
    uint16_t getEventId() const { return _eventId; }

    void raiseEvent(EventQueue *eventQueue);

    WidgetStyle style;
private:
    uint16_t _left;
    uint16_t _top;
    uint16_t _width;
    uint16_t _height;
    uint8_t _leftPadding;
    uint8_t _topPadding;
    bool _isFocus;
    uint16_t _eventId;

};

#endif          // WIDGET_H
