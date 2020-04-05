// TextWidget

#ifndef TEXT_WIDGET_H
#define TEXT_WIDGET_H

#include <Widget.h>

class TextWidget: public Widget
{
public:
    TextWidget(uint16_t eventId, uint16_t left, uint16_t top, uint16_t width, uint16_t height, String text);
    TextWidget(uint16_t eventId, uint16_t width, uint16_t height, String text);
    TextWidget(const TextWidget &textWidget);
    TextWidget();

    String getText() const { return _text; }
    void setText(String text) { _text = text; }
    void draw(M5Display *lcd);

private:
    String _text;

};



#endif                  // TEXT_WIDGET_H
