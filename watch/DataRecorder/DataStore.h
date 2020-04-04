/*

    DataStore


*/


#ifndef DATA_STORE_H
#define DATA_STORE_H

#include "SensorValue.h"
#include "DataStoreItem.h"


#define DATA_STORE_BUFFER_SIZE                  65


class DataStore
{
public:
    DataStore();

    void clear();
    void add(SensorValue &accel, SensorValue &gyro);
    bool isBufferFull();
    size_t saveBuffer(String filename);
    uint8_t getRecordSize() { return DATA_STORE_STREAM_SIZE; }

private:
    uint16_t _dataIndex;
    DataStoreItem _buffer[DATA_STORE_BUFFER_SIZE];
    uint8_t _bufferIndex;
};


#endif                  // DATA_STORE_H
