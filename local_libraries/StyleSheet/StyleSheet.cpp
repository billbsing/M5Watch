/*

    StyleSheet


*/

#include "StyleSheet.h"

StyleSheet::StyleSheet(StyleItem *styleItems):
_styleItems(styleItems) {

}

StyleSheet::StyleSheet(StyleSheet *styleSheet) {
    if ( styleSheet ) {
        _styleItems = styleSheet->getItems();
    }
}


uint16_t StyleSheet::getValue(uint16_t styleId, uint16_t defaultValue) const {
    if ( _styleItems ) {
        for ( uint8_t index; index < 255 && _styleItems[index].styleId != 0; index ++) {
            if (_styleItems[index].styleId == styleId) {
                return _styleItems[index].value;
            }
        }
    }
    return defaultValue;
}
