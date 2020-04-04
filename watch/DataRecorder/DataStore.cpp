/*

    DataStore

*/

#include <TimeLib.h>
#include "DataStore.h"
#include "DataStoreItem.h"


DataStore::DataStore():
_dataIndex(0),
_bufferIndex(0) {
    // memset(&_buffer, 0, sizeof(DataStoreItem) * DATA_STORE_BUFFER_SIZE);
}

void DataStore::add(SensorValue &accel, SensorValue &gyro) {
    DataStoreItem *item = &_buffer[_bufferIndex];
    item->setAccel(accel);
    item->setGyro(gyro);
    item->setIndex(_dataIndex);
    item->setTimeStamp(now());
    _dataIndex ++;
    _bufferIndex ++;
    if ( _bufferIndex >= DATA_STORE_BUFFER_SIZE) {
        _bufferIndex = 0;
    }
}
