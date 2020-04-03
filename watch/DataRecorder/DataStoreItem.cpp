/*


    DataStoreItem.cpp

*/
#include "DataStoreItem.h"

DataStoreItem::DataStoreItem() {

}

void DataStoreItem::setAccel(DataItem &item) {
    memcpy(&_accel, &item, sizeof(DataItem));
}

void DataStoreItem::setGyro(DataItem &item) {
    memcpy(&_gyro, &item, sizeof(DataItem));
}

void DataStoreItem::readFromStream(Stream *stream) {
    StreamReader streamReader(stream);
    _state.value = streamReader.readByte();
    _millis = streamReader.readDWord();
    _time = streamReader.readDWord();
    _accel.x = streamReader.readFloat();
    _accel.y = streamReader.readFloat();
    _accel.z = streamReader.readFloat();
    _gyro.x = streamReader.readFloat();
    _gyro.y = streamReader.readFloat();
    _gyro.z = streamReader.readFloat();
}

size_t DataStoreItem::writeToStream(Stream *stream) {
    StreamWriter streamWriter(stream);
    size_t size = 0;
    size += streamWriter.writeByte(_state.value);
    size += streamWriter.writeDWord(_millis);
    size += streamWriter.writeDWord(_time);
    size += streamWriter.writeFloat(_accel.x);
    size += streamWriter.writeFloat(_accel.y);
    size += streamWriter.writeFloat(_accel.z);
    size += streamWriter.writeFloat(_gyro.x);
    size += streamWriter.writeFloat(_gyro.y);
    size += streamWriter.writeFloat(_gyro.z);
    return size;
}
