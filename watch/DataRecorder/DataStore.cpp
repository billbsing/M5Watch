/*

    DataStore

*/

#include <TimeLib.h>
#include <SPIFFS.h>
#include <StreamString.h>

#include "M5Watch.h"
#include "DataStore.h"
#include "DataStoreItem.h"


DataStore::DataStore(String filename):
_filename(filename),
_dataIndex(0),
_bufferIndex(0),
_bufferCount(0) {
    // memset(&_buffer, 0, sizeof(DataStoreItem) * DATA_STORE_BUFFER_SIZE);
}

void DataStore::readHeader() {
    if (SPIFFS.begin()) {
        File file = SPIFFS.open(_filename.c_str(), FILE_READ);
        if (file) {
            file.seek(0, SeekSet);
            _header.readFromStream(file);
            file.close();
        }
        SPIFFS.end();
    }
}

void DataStore::clear() {
    clearBuffer();
    _header.clear();
}

void DataStore::clearBuffer() {
    for ( uint8_t index = 0; index < DATA_STORE_BUFFER_SIZE; index ++) {
        _buffer[index].clear();
    }
    _bufferIndex = 0;
    _bufferCount = 0;
}

void DataStore::deleteFile() {
    if (SPIFFS.begin()) {
        SPIFFS.remove(_filename);
        clear();
        SPIFFS.end();
    }
}

void DataStore::add(SensorValue &accel, SensorValue &gyro) {
    DataStoreItem *item = &_buffer[_bufferIndex];
    item->setAccel(accel);
    item->setGyro(gyro);
    item->setIndex(_dataIndex);
    item->setTimeStamp(now());
    _dataIndex ++;
    _bufferIndex ++;
    _bufferCount ++;
    if ( _bufferIndex >= DATA_STORE_BUFFER_SIZE) {
        _bufferIndex = 0;
    }
}

bool DataStore::isBufferFull() {
    return _bufferIndex >= DATA_STORE_BUFFER_SIZE - 2;
}

void DataStore::saveBufferToFile() {
    size_t size = 0;
    uint16_t writeCount = 0;
    if (SPIFFS.begin()) {
        File file = SPIFFS.open(_filename.c_str(), FILE_WRITE);
        if (file) {
            if ( ((int32_t)file.size()) <= 0) {
                size = _header.writeToStream(file);
            }
            file.seek(0, SeekEnd);
            for ( uint8_t index = 0; index < _bufferIndex; index ++) {
                size += _buffer[index].writeToStream(file);
                writeCount ++;
            }
            if ( writeCount > 0) {
                _header.addWriteCount(writeCount);
                file.seek(0, SeekSet);
                _header.writeToStream(file);
                clearBuffer();
            }
            file.close();
        }
        SPIFFS.end();
    }
}

size_t DataStore::getItemIndexPosition(uint32_t fileIndex) {
    size_t position = uint32_t(DATA_STORE_HEADER_SIZE);
    position += fileIndex * uint32_t(DATA_STORE_ITEM_SIZE);
    return position;
}

DataStoreItem &DataStore::readItemFromFile(uint32_t fileIndex) {
    if (SPIFFS.begin()) {
        File file = SPIFFS.open(_filename.c_str(), FILE_READ);
        if (file) {
            _item.clear();
            file.seek(getItemIndexPosition(fileIndex), SeekSet);
            _item.readFromStream(file);
            _item.setIndexInFile(fileIndex);
            file.close();
        }
        SPIFFS.end();
    }
    return _item;
}

bool DataStore::writeItemToFile(uint32_t fileIndex, const DataStoreItem &item) {
    bool result = false;
    if (SPIFFS.begin()) {
        File file = SPIFFS.open(_filename.c_str(), FILE_WRITE);
        if (file) {
            file.seek(getItemIndexPosition(fileIndex), SeekSet);
            item.writeToStream(file);
            file.close();
            result = true;
        }
        SPIFFS.end();
    }
    return result;
}

bool DataStore::uploadItem(IPAddress server, uint16_t port) {
    uint16_t dataSize = DATA_STORE_BUFFER_SIZE;
    StreamString outStream;
    DataStoreItem item;
    WiFiClient client;
    if (client.connect(server, port) ) {
        uint32_t fileIndex = _header.getNextUploadIndex();
        item = readItemFromFile(fileIndex);
        if (!item.isEmpty()) {
            outStream.write((uint8_t *)&dataSize, sizeof(uint16_t));
            item.writeToStream(outStream);
            client.write(outStream);
            outStream.clear();
        }
    }
    return false;
}
