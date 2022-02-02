#include "WidgetStyle.h"


WidgetStyle::WidgetStyle(const WidgetStyle& widgetStyle):
_textColor(widgetStyle.getTextColor()),
_backgroundColor(widgetStyle.getBackgroundColor()),
_lineColor(widgetStyle.getLineColor()),
_textSize(widgetStyle.getTextSize()) {

}

WidgetStyle::WidgetStyle(uint16_t textColor, uint16_t backgroundColor, \
            uint16_t lineColor, uint8_t textSize):
_textColor(textColor),
_backgroundColor(backgroundColor),
_lineColor(lineColor),
_textSize(textSize) {

}
