/*


    Style Sheet

*/

#ifndef STYLE_SHHET_H
#define STYLE_SHEET_H

#include "../core.h"
#include "StylesCore.h"

#define STYLE_END           {0x0000, 0x0000}

typedef struct {
    uint16_t styleId;
    uint16_t value;
} StyleItem;

class StyleSheet
{
public:
    StyleSheet(StyleItem *styleItems);
    StyleSheet(): StyleSheet((StyleItem *) NULL) {}
    StyleSheet(StyleSheet *styleSheet);

    StyleItem *getItems() const { return _styleItems; }
    uint16_t getValue(uint16_t styleId, uint16_t defaultValue) const;

private:
    StyleItem *_styleItems;
};

#endif                      // STYLE_SHEET_H
