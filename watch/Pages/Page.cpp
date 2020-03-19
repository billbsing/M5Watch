#include "Page.h"
#include "PageManager.h"

Page::Page(PageManager &manager):
_manager(manager),
_eventIndex(0),
_index(0) {

}

uint16_t Page::getNextEventId() {
    // eventId is a 2 * bytes [page index, eventIndex]
    uint16_t eventId = _index;
    eventId <<= 8;
    _eventIndex ++;
    eventId |= _eventIndex;
    return eventId;
}
