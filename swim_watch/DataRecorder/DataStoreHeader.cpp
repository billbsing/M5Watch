/*

    DataStoreHeader

*/
#include <StreamReader.h>
#include <StreamWriter.h>

#include "DataStoreHeader.h"

DataStoreHeader::DataStoreHeader():
_storeCount(0),
_uploadCount(0),
_waitForUploadCount(0),
_nextUploadIndex(0) {

}

DataStoreHeader::DataStoreHeader(const DataStoreHeader &header):
_storeCount(header.getStoreCount()),
_uploadCount(header.getUploadCount()),
_waitForUploadCount(header.getWaitForUploadCount()),
_nextUploadIndex(header.getNextUploadIndex()) {

}

void DataStoreHeader::clear() {
    _storeCount = 0;
    _uploadCount = 0;
    _waitForUploadCount = 0;
    _nextUploadIndex = 0;
}

void DataStoreHeader::addWriteCount(uint16_t value) {
    _storeCount += value;
    _waitForUploadCount += value;
}

void DataStoreHeader::addUploadCount(uint16_t value) {
    _waitForUploadCount -= value;
}

void DataStoreHeader::setNextUploadIndex(uint16_t nextUploadIndex) {
    _nextUploadIndex = nextUploadIndex;
    _uploadCount ++;
    _waitForUploadCount --;
}

void DataStoreHeader::readFromStream(Stream &stream) {
    StreamReader reader(&stream);
    uint8_t headerId = reader.readByte();
    uint8_t version = reader.readByte();
    _storeCount = reader.readWord();
    _uploadCount = reader.readWord();
    _waitForUploadCount = reader.readWord();
    _nextUploadIndex = reader.readWord();
}

size_t DataStoreHeader::writeToStream(Stream &stream) const {
    StreamWriter writer(&stream);
    size_t size = 0;
    size += writer.writeByte(DATA_STORE_STREAM_HEADER_ID);
    size += writer.writeByte(1);
    size += writer.writeWord(_storeCount);
    size += writer.writeWord(_uploadCount);
    size += writer.writeWord(_waitForUploadCount);
    size += writer.writeWord(_nextUploadIndex);
    return size;
}
