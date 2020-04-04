/*

    SensorValue

*/

#ifndef SENSOR_VALUE_H
#define SENSOR_VALUE_H

#include <PersistentFile.h>

class SensorValue
{
public:
    SensorValue();
    SensorValue(const SensorValue &sensorValue);

    void clear();
    void readFromStream(Stream *stream);
    size_t writeToStream(Stream *stream);

    float getX() const { return _x; }
    float *getXPtr() { return &_x; }
    void setX(float value) { _x = value; }

    float getY() const { return _y; }
    float *getYPtr() { return &_x; }
    void setY(float value) { _y = value; }

    float getZ() const { return _z; }
    float *getZPtr() { return &_x; }
    void setZ(float value) { _z = value; }

    SensorValue &operator + (const SensorValue &sensorValue);
    SensorValue &operator / (const uint16_t value);
    void operator += (const SensorValue &sensorValue);
    void operator = (const float value);

private:
    float _x;
    float _y;
    float _z;

};



#endif              // SENSOR_VALUE_H
