/*


    DataStoreItem.cpp

*/
#include <StreamReader.h>
#include <StreamWriter.h>

#include "M5Watch.h"
#include "DataStoreItem.h"

DataStoreItem::DataStoreItem() {

}

void DataStoreItem::clear() {
    _state.value = 0;
    _timeStamp = 0;
    _index = 0;
    _accel = 0.0f;
    _gyro = 0.0f;
}

void DataStoreItem::setAccel(SensorValue &sensorValue) {
    _accel = sensorValue;
}

void DataStoreItem::setGyro(SensorValue &sensorValue) {
    _gyro = sensorValue;
}

void DataStoreItem::readFromStream(Stream &stream) {
    StreamReader reader(&stream);
    uint8_t headerId = reader.readByte();
    _state.value = reader.readByte();
    _timeStamp = reader.readDWord();
    _index = reader.readWord();
    _accel.readFromStream(stream);
    _gyro.readFromStream(stream);
}

size_t DataStoreItem::writeToStream(Stream &stream) const {
    StreamWriter writer(&stream);
    size_t size = 0;
    // size -> 1 + 1 + 4 + 2 + ( 6 * 4) = 34 bytes
    // debug.print("write: %d %ld %d", _state.value, _timeStamp, _index);
    size += writer.writeByte(DATA_STORE_STREAM_ITEM_ID);
    size += writer.writeByte(_state.value);
    size += writer.writeDWord(_timeStamp);
    size += writer.writeWord(_index);
    size += _accel.writeToStream(stream);
    size += _gyro.writeToStream(stream);
    return size;
}

size_t DataStoreItem::writeTextToStream(Stream &stream) const {
    size_t size;
    size += stream.print(_timeStamp);
    size += stream.print(',');
    size += stream.print(_index);
    size += stream.print(',');
    size += _accel.writeTextToStream(stream);
    size += stream.print(',');
    size += _gyro.writeTextToStream(stream);
    return size;
}
