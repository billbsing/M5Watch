/*

    StyleSheet


*/

#include "StyleSheet.h"

StyleSheet::StyleSheet(StyleItem *styleItems):
_styleItems(styleItems) {

}

StyleSheet::StyleSheet(StyleSheet *styleSheet):
_styleItems(NULL) {
    if ( styleSheet ) {
        _styleItems = styleSheet->getItems();
    }
}


uint16_t StyleSheet::getValue(uint16_t styleId, uint16_t defaultValue) const {
    if ( _styleItems != NULL ) {
        for ( uint8_t index; index < 250 && _styleItems[index].styleId != 0; index ++) {
            if (_styleItems[index].styleId == styleId) {
                return _styleItems[index].value;
            }
        }
    }
    return defaultValue;
}
