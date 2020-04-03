/*

    SwimLapCounter

*/

#include "M5Watch.h"
#include "DataRecorder.h"

DataRecorder::DataRecorder(String filename):
_gyro({0, 0, 0}),
_accel({0, 0, 0}),
_avgGyro({0, 0, 0}),
_avgAccel({0, 0, 0}),
_avgCounter(0),
_status(dataIdle),
_filename(filename) {

}

void DataRecorder::loop() {
    DataItem gyro;
    DataItem accel;

    M5.Mpu6886.getAccelData(&accel.x,&accel.y,&accel.z);
    _avgAccel.x += accel.x;
    _avgAccel.y += accel.y;
    _avgAccel.z += accel.z;

    M5.Mpu6886.getGyroData(&gyro.x,&gyro.y,&gyro.z);
    _avgGyro.x += gyro.x;
    _avgGyro.y += gyro.y;
    _avgGyro.z += gyro.z;

    _avgCounter ++;
    if ( _avgCounter == 100 ) {
        _accel.x = _avgAccel.x / _avgCounter;
        _accel.y = _avgAccel.y / _avgCounter;
        _accel.z = _avgAccel.z / _avgCounter;

        _gyro.x = _avgGyro.x / _avgCounter;
        _gyro.y = _avgGyro.y / _avgCounter;
        _gyro.z = _avgGyro.z / _avgCounter;

        _avgAccel.x = 0;
        _avgAccel.y = 0;
        _avgAccel.z = 0;

        _avgGyro.x = 0;
        _avgGyro.y = 0;
        _avgGyro.z = 0;
        _avgCounter = 0;

        eventQueue.push(EVENT_DATA_ON_CHANGE);
    }
}
