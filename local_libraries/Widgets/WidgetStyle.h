// WidgetStyle Base Class

#ifndef WIDGET_STYLE_H
#define WIDGET_STYLE_H

#include <Arduino.h>
#include <M5StickC.h>

class WidgetStyle
{
public:
    WidgetStyle() {;}
    WidgetStyle(const WidgetStyle &widgetStyle);
    WidgetStyle(uint16_t textColor, uint16_t backgroundColor, uint16_t focusColor, \
                uint16_t nonFocusColor, uint8_t textSize);

    uint16_t getTextColor() const { return _textColor; }
    void setTextColor(uint16_t value) { _textColor = value; }

    uint16_t getBackgroundColor() const { return _backgroundColor; }
    void setBackgroundColor(uint16_t value) { _backgroundColor = value; }

    uint16_t getFocusColor() const { return _focusColor; }
    void setFocusColor(uint16_t value) { _focusColor = value; }

    uint16_t getNonFocusColor() const { return _nonFocusColor; }
    void setNonFocusColor(uint16_t value) { _nonFocusColor = value; }

    uint8_t getTextSize() const { return _textSize; }
    void setTextSize(uint8_t value) { _textSize = value; }

private:
    uint16_t _textColor;
    uint16_t _backgroundColor;
    uint16_t _focusColor;
    uint16_t _nonFocusColor;
    uint8_t _textSize;
};

#endif              // WIDGET_STYLE_H
