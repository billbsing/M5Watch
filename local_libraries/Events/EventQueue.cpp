#include "EventQueue.h"

EventQueue::EventQueue() :
_length(0),
_maxCount(0) {
    memset(_items, 0, sizeof(EventItem) *  EVENT_QUEUE_SIZE);
}

void EventQueue::push(uint16_t eventId, uint32_t delayMillis, bool isReplace) {
    uint8_t i;
    bool isEmptyFound = false;
    if ( isReplace ) {
        remove(eventId);
    }
    for ( i = 0; i < EVENT_QUEUE_SIZE && i < _length; i ++) {
        if ( _items[i].eventId == 0 ) {
            _items[i].eventId = eventId;
            _items[i].timeoutMillis = millis() + delayMillis;
            isEmptyFound = true;
            break;
        }
    }

    if ( !isEmptyFound ) {
        if ( _length < EVENT_QUEUE_SIZE ) {
            _items[_length].eventId = eventId;
            _items[_length].timeoutMillis = millis() + delayMillis;
            _length ++;
        }
    }
    if ( _length > _maxCount ) {
        _maxCount = _length;
    }
}

void EventQueue::shiftStackDown(uint8_t startPosition) {
    // move the stack down one
    uint8_t i;
    for ( i = startPosition ; i < EVENT_QUEUE_SIZE - 1; i ++ ) {
        _items[i].eventId = _items[i + 1].eventId;
        _items[i].timeoutMillis = _items[i + 1].timeoutMillis;
    }
}

uint16_t EventQueue::pop() {
    uint16_t eventId = 0;
    uint8_t i, stackI;
    for ( i = 0; i < EVENT_QUEUE_SIZE && i < _length; i ++) {
        if ( _items[i].eventId != 0
                && (millis() - _items[i].timeoutMillis) >= 0
                && (millis() - _items[i].timeoutMillis) < LONG_MAX ) {
            eventId = _items[i].eventId;
            shiftStackDown(i);
            _length --;
            break;
        }
    }
    return eventId;
}

void EventQueue::remove(uint16_t eventId) {
    uint8_t i;
    bool isFound = false;
    do {
        isFound = false;
        for ( i = 0; i < EVENT_QUEUE_SIZE && i < _length; i ++) {
            if ( _items[i].eventId == eventId  && eventId != 0 ) {
                shiftStackDown(i);
                isFound = true;
                break;
            }
        }
    } while ( isFound );
}

uint8_t EventQueue::getQueueSize() {
    uint8_t count = 0;
    uint8_t i;
    for ( i = 0; i < EVENT_QUEUE_SIZE && i < _length; i ++) {
        if ( _items[i].eventId != 0
                && (millis() - _items[i].timeoutMillis) >= 0
                && (millis() - _items[i].timeoutMillis) < LONG_MAX ) {
            count ++;
        }
    }
    return count;

}
bool EventQueue::isEmpty() {
    return getQueueSize() == 0;
}
