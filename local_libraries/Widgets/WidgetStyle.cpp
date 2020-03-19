#include <WidgetStyle.h>


WidgetStyle::WidgetStyle(const WidgetStyle& widgetStyle):
_textColor(widgetStyle.getTextColor()),
_backgroundColor(widgetStyle.getBackgroundColor()),
_focusColor(widgetStyle.getFocusColor()),
_nonFocusColor(widgetStyle.getNonFocusColor()),
_textSize(widgetStyle.getTextSize()) {

}

WidgetStyle::WidgetStyle(uint16_t textColor, uint16_t backgroundColor, uint16_t focusColor, \
            uint16_t nonFocusColor, uint8_t textSize):
_textColor(textColor),
_backgroundColor(backgroundColor),
_focusColor(focusColor),
_nonFocusColor(nonFocusColor),
_textSize(textSize) {

}
