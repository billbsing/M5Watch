/*

    SensorValue

*/

#include "SensorValue.h"

SensorValue::SensorValue():
_x(0),
_y(0),
_z(0) {
}

SensorValue::SensorValue(const SensorValue &sensorValue) {
    _x = sensorValue.getX();
    _y = sensorValue.getY();
    _z = sensorValue.getZ();
}
void SensorValue::clear() {
    _x = 0;
    _y = 0;
    _z = 0;
}

void SensorValue::readFromStream(Stream *stream) {
    StreamReader streamReader(stream);
    _x = streamReader.readFloat();
    _y = streamReader.readFloat();
    _z = streamReader.readFloat();

}
size_t SensorValue::writeToStream(Stream *stream) {
    StreamWriter streamWriter(stream);
    size_t size = 0;
    size += streamWriter.writeFloat(_x);
    size += streamWriter.writeFloat(_y);
    size += streamWriter.writeFloat(_z);
    return size;
}

SensorValue &SensorValue::operator + (const SensorValue &sensorValue) {
    SensorValue value;
    value.setX(_x + sensorValue.getX());
    value.setY(_y + sensorValue.getY());
    value.setZ(_z + sensorValue.getZ());
    return value;
}

SensorValue &SensorValue::operator / (const uint16_t value) {
    SensorValue sensorValue;
    sensorValue.setX( _x / value );
    sensorValue.setY( _y / value );
    sensorValue.setZ( _z / value );
    return sensorValue;
}

void SensorValue::operator += (const SensorValue &sensorValue){
    _x += sensorValue.getX();
    _y = sensorValue.getY();
    _x = sensorValue.getZ();
}

void SensorValue::operator = (const float value){
    _x = value;
    _y = value;
    _x = value;
}
