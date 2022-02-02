// WidgetStyle Base Class

#ifndef WIDGET_STYLE_H
#define WIDGET_STYLE_H

#include "../core.h"


class WidgetStyle
{
public:
    WidgetStyle() {;}
    WidgetStyle(const WidgetStyle &widgetStyle);
    WidgetStyle(uint16_t textColor, uint16_t backgroundColor, \
                uint16_t lineColor, uint8_t textSize);

    uint16_t getTextColor() const { return _textColor; }
    void setTextColor(uint16_t value) { _textColor = value; }

    uint16_t getBackgroundColor() const { return _backgroundColor; }
    void setBackgroundColor(uint16_t value) { _backgroundColor = value; }

    uint16_t getLineColor() const { return _lineColor; }
    void setLineColor(uint16_t value) { _lineColor = value; }

    uint8_t getTextSize() const { return _textSize; }
    void setTextSize(uint8_t value) { _textSize = value; }

private:
    uint16_t _textColor;
    uint16_t _backgroundColor;
    uint16_t _lineColor;
    uint8_t _textSize;
};

#endif              // WIDGET_STYLE_H
