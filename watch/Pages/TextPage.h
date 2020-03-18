// TextPage

#ifndef TEXT_PAGE_H
#define TEXT_PAGE_H


#include "Page.h"

class TextPage: public Page
{
public:
    TextPage(String text): _text(text){}

    void loadWidgets(WidgetManager *manager);
    void show(M5Display &lcd);
    void processEvent(uint16_t eventId);

private:
    String _text;
};


#endif          // TEXT_PAGE_H
