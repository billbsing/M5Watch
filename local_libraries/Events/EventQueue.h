#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <Arduino.h>
#include <limits.h>

#define EVENT_QUEUE_SIZE        40

typedef struct {
    uint16_t eventId;
    uint32_t timeoutMillis;
} EventItem;

class EventQueue {

public:
    EventQueue();
    void push(uint16_t eventId, uint32_t delayMillis, bool isReplace);
    void push(uint16_t eventId, uint32_t delayMillis) { push(eventId, delayMillis, false); }
    void push(uint16_t eventId, bool isReplace) { push(eventId, 0, isReplace); }
    void push(uint16_t eventId) { push(eventId, 0, false); }

    uint16_t pop();
    void remove(uint16_t eventId);

    uint8_t getQueueSize();
    bool isEmpty();
    uint8_t getMaxCount() { return _maxCount; }

protected:
    void shiftStackDown(uint8_t startPosition);

private:
    EventItem _items[EVENT_QUEUE_SIZE];
    uint8_t _length;
    uint8_t _maxCount;

};

#endif              // EVENT_QUEUE_H
