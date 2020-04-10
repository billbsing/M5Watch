// TextPage

#ifndef TEXT_PAGE_H
#define TEXT_PAGE_H


#include <Page.h>

class TextPage: public Page
{
public:
    TextPage();

    void init();
    void begin();
    void end();
    void loadWidgets(WidgetManager *manager);
    void draw(M5Display *lcd);
    void processEvent(uint16_t eventId);

    void setText(String value) { _text = value; }
    String getText() const { return _text; }

private:
    String _text;
};


#endif          // TEXT_PAGE_H
