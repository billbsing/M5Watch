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
    void saveBuffer(String filename);
    size_t getSize() { return _size; }
    void setSize(size_t value) { _size = value;}

    size_t getCount() { return _size / DATA_STORE_STREAM_SIZE; }

private:
    uint16_t _dataIndex;
    DataStoreItem _buffer[DATA_STORE_BUFFER_SIZE];
    uint8_t _bufferIndex;
    size_t _size;
};


#endif                  // DATA_STORE_H
