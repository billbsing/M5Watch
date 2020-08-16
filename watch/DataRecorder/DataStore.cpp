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

bool DataStore::readItemFromFile(uint32_t fileIndex, DataStoreItem *item, DataStoreHeader *header) {
    bool result = false;
    item->clear();
    if (SPIFFS.begin()) {
        File file = SPIFFS.open(_filename.c_str(), FILE_READ);
        if (file) {
            file.seek(getItemIndexPosition(fileIndex), SeekSet);
            item->readFromStream(file);
            item->setIndexInFile(fileIndex);
            if (header) {
                file.seek(0, SeekSet);
                header->readFromStream(file);
            }
            file.close();
            result = true;
        }
        SPIFFS.end();
    }
    return result;
}

bool DataStore::writeItemToFile(uint32_t fileIndex, DataStoreItem *item, DataStoreHeader *header) {
    bool result = false;
    if (SPIFFS.begin()) {
        File file = SPIFFS.open(_filename.c_str(), FILE_WRITE);
        if (file) {
            file.seek(getItemIndexPosition(fileIndex), SeekSet);
            item->writeToStream(file);
            if (header) {
                file.seek(0, SeekSet);
                header->writeToStream(file);
            }
            file.close();
            result = true;
        }
        SPIFFS.end();
    }
    return result;
}

bool DataStore::uploadConnect(IPAddress &server, uint16_t port) {
    debug.print("connecting %s:%d", server.toString().c_str(), port);
    if (_client.connect(server, port) ) {
        return true;
    }
    debug.print("connection failed");
    return false;
}

bool DataStore::uploadSend() {
    uint16_t dataSize = DATA_STORE_BUFFER_SIZE;
    StreamString outStream;
    DataStoreItem item;
    if (_client) {
        _uploadIndex = _header.getNextUploadIndex();
        debug.print("sending index %ld", _uploadIndex);
        if (readItemFromFile(_uploadIndex, &_uploadItem, &_header) ){
            outStream.write((uint8_t *)&dataSize, sizeof(uint16_t));
            _uploadItem.writeToStream(outStream);
            _client.write(outStream);
            outStream.clear();
            return true;
        }
    }
    return false;
}

bool DataStore::uploadReply() {
    time_t timeoutTime = now() + 5;
    uint8_t readBuffer[DATA_STORE_READ_PACKET_SIZE + 1];
    debug.print("waiting for index %ld", _uploadIndex);
    if (_uploadItem.isEmpty()) {
        return false;
    }
    while(now() < timeoutTime) {
        if (_client.available()) {
            int packetLength = _client.read();
            debug.print("read length: %d", packetLength);
            if (packetLength < DATA_STORE_READ_PACKET_SIZE) {
                memset(readBuffer, 0, DATA_STORE_READ_PACKET_SIZE);
                _client.read(readBuffer, packetLength);
                if ( readBuffer[0] == DATA_STORE_STREAM_HEADER_ID) {
                    unsigned long itemIndex = readBuffer[1];
                    debug.print("write index %ld", itemIndex);
                    if ( itemIndex > 0) {
                        ItemState state = _uploadItem.getState();
                        state.isUpload = true;
                        _uploadItem.setState(state);
                        _header.setNextUploadIndex(_uploadIndex + 1);
                        writeItemToFile(_uploadIndex, &_uploadItem, &_header);
                        _uploadItem.clear();
                        return true;
                    }
                    break;
                }
            }
        }
    }
    return false;
}
