/*

    SensorValue

*/
#include "M5Watch.h"
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
    debug.print("Copy constructor %f,%f,%f", _x, _y, _z);
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

SensorValue SensorValue::operator + (const SensorValue &sensorValue) const {
    SensorValue newValue;
    newValue.setX(_x + sensorValue.getX());
    newValue.setY(_y + sensorValue.getY());
    newValue.setZ(_z + sensorValue.getZ());
    return newValue;
}

SensorValue SensorValue::operator / (const uint16_t value) const {
    SensorValue newValue;
    float divisor = value;
    if ( fabs(divisor) > 0.0f ) {
        newValue.setX( _x / divisor );
        newValue.setY( _y / divisor );
        newValue.setZ( _z / divisor );
    }
    return newValue;
}

void SensorValue::operator += (const SensorValue &sensorValue) {
    _x += sensorValue.getX();
    _y += sensorValue.getY();
    _z += sensorValue.getZ();
}

SensorValue &SensorValue::operator = (const SensorValue &sensorValue) {
    if ( this == &sensorValue ) {
        return *this;
    }
    _x = sensorValue.getX();
    _y = sensorValue.getY();
    _z = sensorValue.getZ();
    return *this;
}


void SensorValue::operator = (const float value) {
    _x = value;
    _y = value;
    _x = value;
}
