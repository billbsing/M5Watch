#ifndef EVENT_GROUP_H
#define EVENT_GROUP_H

#include "core.h"
#include <limits.h>

#define EVENT_GROUP_SIZE        40

typedef struct {
    uint16_t groupId;
    uint16_t eventId;
} EventGroupItem;

class EventGroup {

public:
    EventGroup();
    void assign(uint16_t groupId, uint16_t eventId);
    uint8_t readList(uint16_t groupId, uint16_t *data, uint8_t maxLength);
    uint8_t getCount();

private:
    EventGroupItem _items[EVENT_GROUP_SIZE];

};

#endif              // EVENT_GROUP_H
