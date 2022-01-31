/*

    DataStoreHeader

*/

#ifndef DATA_STORE_HEADER_H
#define DATA_STORE_HEADER_H


#define DATA_STORE_STREAM_HEADER_ID            0xA2
#define DATA_STORE_HEADER_SIZE                 10

class DataStoreHeader
{
public:
    DataStoreHeader();
    DataStoreHeader(const DataStoreHeader &header);

    void clear();

    uint16_t getStoreCount() const { return _storeCount; }
    uint16_t getUploadCount() const { return _uploadCount; }
    uint16_t getWaitForUploadCount() const { return _waitForUploadCount; }
    uint16_t getNextUploadIndex() const { return _nextUploadIndex; }

    void addWriteCount(uint16_t value);
    void addUploadCount(uint16_t value);

    void setNextUploadIndex(uint16_t nextUploadIndex);
    // StreamData
    void readFromStream(Stream &stream);
    size_t writeToStream(Stream &stream) const;

private:
    uint16_t _storeCount;
    uint16_t _uploadCount;
    uint16_t _waitForUploadCount;
    uint16_t _nextUploadIndex;

};


#endif                  // DATA_STORE_HEADER_H
