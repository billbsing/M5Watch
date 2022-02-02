#include "EventGroup.h"

EventGroup::EventGroup() {
    memset(_items, 0, sizeof(EventGroupItem) *  EVENT_GROUP_SIZE);
}


void EventGroup::assign(uint16_t groupId, uint16_t eventId) {
    uint8_t i;
    for (i = 0; i < EVENT_GROUP_SIZE; i ++) {
        if ( _items[i].groupId == 0) {
            _items[i].groupId = groupId;
            _items[i].eventId = eventId;
            break;
        }
    }
}

uint8_t EventGroup::readList(uint16_t groupId, uint16_t *data, uint8_t maxLength) {
    uint8_t i;
    uint8_t dataCount = 0;
    for ( i = 0; i < EVENT_GROUP_SIZE; i ++) {
        if ( _items[i].groupId == groupId) {
            data[dataCount] = _items[i].eventId;
            dataCount ++;
            if ( dataCount == maxLength) {
                break;
            }
        }
    }
    return dataCount;
}

uint8_t EventGroup::getCount() {
    uint8_t i;
    uint8_t count = 0;
    for ( i = 0; i < EVENT_GROUP_SIZE; i ++) {
        if ( _items[i].groupId != 0 ) {
            count ++;
        }
    }
    return count;
}
