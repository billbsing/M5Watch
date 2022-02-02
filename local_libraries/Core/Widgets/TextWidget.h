// TextWidget

#ifndef TEXT_WIDGET_H
#define TEXT_WIDGET_H

#include "Widget.h"

class TextWidget: public Widget
{
public:
    TextWidget(const TextWidget &textWidget);
    TextWidget();

    String getText() const { return _text; }
    void setText(String text) { _text = text; }
    void draw(M5Display *lcd);

private:
    String _text;

};



#endif                  // TEXT_WIDGET_H
