/*

    DataStoreItem


*/


#ifndef DATA_STORE_ITEM_H
#define DATA_STORE_ITEM_H

#include "SensorValue.h"

#define DATA_STORE_STREAM_ITEM_ID                   0xA2
#define DATA_STORE_ITEM_SIZE                        34

union ItemState {
    struct {
        uint8_t isUpload : 1;
        uint8_t isStart : 1;
        uint8_t isStop : 1;
        uint8_t isTurn : 1;
        uint8_t isStroke : 1;
    };
    uint8_t value;
};

class DataStoreItem
{
public:
    DataStoreItem();

    void clear();

    bool isEmpty() const { return _timeStamp == 0 && _index == 0; }

    SensorValue getAccel() const { return _accel; }
    void setAccel(SensorValue &sensorValue);

    SensorValue getGyro() const { return _gyro; }
    void setGyro(SensorValue &sensorValue);

    uint16_t getIndex() const { return _index; }
    void setIndex(uint16_t value) { _index = value; }

    uint32_t getTimeStamp() const { return _timeStamp; }
    void setTimeStamp(uint32_t value) { _timeStamp = value; }

    ItemState getState() const { return _state; }
    void setState(ItemState value) { _state = value; }

    uint32_t getIndexInFile() const { return _indexInFile; }
    void setIndexInFile(uint32_t value) { _indexInFile = value; }

    // PersistentFile
    void readFromStream(Stream &stream);
    size_t writeToStream(Stream &stream) const;

    size_t writeTextToStream(Stream &stream) const;

private:
    uint32_t _indexInFile;
    uint32_t _timeStamp;
    uint16_t _index;
    SensorValue _accel;
    SensorValue _gyro;
    ItemState _state;

};


#endif                  // DATA_STORE_ITEM_H
