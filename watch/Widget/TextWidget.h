// TextWidget

#ifndef TEXT_WIDGET_H
#define TEXT_WIDGET_H

#include <Widget.h>

class TextWidget: public Widget
{
public:
    TextWidget(uint16_t width, uint16_t height, String text);
    TextWidget(uint16_t width, uint16_t height, uint16_t leftPadding, uint16_t topPadding, String text);

    String getText() { return _text; }
    void setText(String text) { _text = text; }
    void show(M5Display &lcd);

private:
    String _text;

};



#endif                  // TEXT_WIDGET_H
