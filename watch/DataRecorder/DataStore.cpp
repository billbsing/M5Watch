/*

    DataStore

*/

#include <TimeLib.h>
#include <SPIFFS.h>
#include "DataStore.h"
#include "DataStoreItem.h"


DataStore::DataStore():
_dataIndex(0),
_bufferIndex(0) {
    // memset(&_buffer, 0, sizeof(DataStoreItem) * DATA_STORE_BUFFER_SIZE);
}

void DataStore::clear() {
    for ( uint8_t index = 0; index < DATA_STORE_BUFFER_SIZE; index ++) {
        _buffer[index].clear();
    }
    _bufferIndex = 0;
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

bool DataStore::isBufferFull() {
    return _bufferIndex == DATA_STORE_BUFFER_SIZE - 2;
}

size_t DataStore::saveBuffer(String filename) {
    size_t size = 0;
    File file = SPIFFS.open(filename.c_str(), FILE_APPEND);
    if ( file ) {
        size = file.size();
        for ( uint8_t index = 0; index < _bufferIndex; index ++) {
            size += _buffer[index].writeToStream(&file);
        }
        file.close();
    }
    clear();
    return size;
}
