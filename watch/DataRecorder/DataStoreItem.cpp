/*


    DataStoreItem.cpp

*/
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

void DataStoreItem::readFromStream(Stream *stream) {
    StreamReader streamReader(stream);
    uint8_t headerId = streamReader.readByte();
    _state.value = streamReader.readByte();
    _timeStamp = streamReader.readDWord();
    _index = streamReader.readWord();
    _accel.readFromStream(stream);
    _gyro.readFromStream(stream);
}

size_t DataStoreItem::writeToStream(Stream *stream) {
    StreamWriter streamWriter(stream);
    size_t size = 0;
    // size -> 1 + 1 + 4 + 2 + ( 6 * 4) = 34 bytes
    size += streamWriter.writeByte(DATA_STORE_STREAM_HEADER_ID);
    size += streamWriter.writeByte(_state.value);
    size += streamWriter.writeDWord(_timeStamp);
    size += streamWriter.writeWord(_index);
    size += _accel.writeToStream(stream);
    size += _gyro.writeToStream(stream);
    return size;
}
