/*

    DataStoreItem


*/


#ifndef DATA_STORE_ITEM_H
#define DATA_STORE_ITEM_H

#include <PersistentFile.h>

#include "SensorValue.h"

#define DATA_STORE_STREAM_HEADER_ID                 0xA2
#define DATA_STORE_STREAM_SIZE                      34

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

    void clear();
    void setAccel(SensorValue &sensorValue);
    void setGyro(SensorValue &sensorValue);
    void setIndex(uint16_t value) { _index = value; }
    void setTimeStamp(uint32_t value) { _timeStamp = value; }

    // PersistentFile
    void readFromStream(Stream *stream);
    size_t writeToStream(Stream *stream);

private:
    uint32_t _timeStamp;
    uint16_t _index;
    SensorValue _accel;
    SensorValue _gyro;
    ItemState _state;

};


#endif                  // DATA_STORE_ITEM_H
