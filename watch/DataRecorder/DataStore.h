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

    void add(SensorValue &accel, SensorValue &gyro);

private:
    uint16_t _dataIndex;
    DataStoreItem _buffer[DATA_STORE_BUFFER_SIZE];
    uint8_t _bufferIndex;
};


#endif                  // DATA_STORE_H
