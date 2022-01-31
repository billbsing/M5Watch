/*

    DataStore


*/


#ifndef DATA_STORE_H
#define DATA_STORE_H

#include "SensorValue.h"
#include "DataStoreItem.h"
#include "DataStoreHeader.h"
#include "WiFiClient.h"

#define DATA_STORE_BUFFER_SIZE                  65
#define DATA_STORE_READ_PACKET_SIZE             20

class DataStore
{
public:
    DataStore(String filename);

    void clear();
    void clearBuffer();
    void readHeader();
    void add(SensorValue &accel, SensorValue &gyro);
    bool isBufferFull();
    uint8_t getBufferCount() { return _bufferCount; }
    void saveBufferToFile();

    String getFilename() const { return _filename; }
    const DataStoreHeader& getHeader() const { return _header; }

    size_t getItemIndexPosition(uint32_t fileIndex);
    bool readItemFromFile(uint32_t fileIndex, DataStoreItem *item,  DataStoreHeader *header);
    bool writeItemToFile(uint32_t fileIndex, DataStoreItem *item, DataStoreHeader *header);
    bool isUploadConnected() { return _client; }
    bool uploadConnect(IPAddress &server, uint16_t port);
    bool uploadSend();
    bool uploadReply();
    void deleteFile();

private:
    String _filename;
    uint16_t _dataIndex;
    DataStoreHeader _header;
    DataStoreItem _buffer[DATA_STORE_BUFFER_SIZE];
    uint8_t _bufferIndex;
    uint8_t _bufferCount;
    WiFiClient _client;
    uint32_t _uploadIndex;
    DataStoreItem _uploadItem;
};


#endif                  // DATA_STORE_H
