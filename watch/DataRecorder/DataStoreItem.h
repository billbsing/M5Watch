/*

    DataStoreItem


*/


#ifndef DATA_STORE_ITEM_H
#define DATA_STORE_ITEM_H

#include "M5Watch.h"
#include <PersistentFile.h>
#include "DataStore.h"

union ItemState {
    struct {
        uint8_t isUpload : 1;
        uint8_t isStart : 1;
        uint8_t isStop : 1;
        uint8_t isTurn : 1;
        uint8_t isStroke : 1;
    };
    uint8_t value;
};

class DataStoreItem: public PersistentFile
{
public:
    DataStoreItem();

    void setAccel(DataItem &item);
    void setGyro(DataItem &item);
    void setMillis(uint32_t value) { _millis = value; }
    void setTime(uint32_t value) { _time = value; }

    // PersistentFile
    void readFromStream(Stream *stream);
    size_t writeToStream(Stream *stream);

private:
    uint32_t _millis;
    uint32_t _time;
    DataItem _accel;
    DataItem _gyro;
    ItemState _state;

};


#endif                  // DATA_STORE_ITEM_H
