/*

    SwimLapCounter

*/

#include "M5Watch.h"
#include "DataRecorder.h"


DataRecorder::DataRecorder(String filename):
_avgCounter(0),
_status(dataIdle),
_filename(filename) {

}

void DataRecorder::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_DATA_START:
            _status = dataRecord;
            eventQueue.push(EVENT_DATA_ON_CHANGE);
        break;
        case EVENT_DATA_STOP:
            _status = dataIdle;
            eventQueue.push(EVENT_DATA_ON_CHANGE);
        break;
        case EVENT_DATA_UPLOAD:
            _status = dataUpload;
            eventQueue.push(EVENT_DATA_ON_CHANGE);
        break;
        case EVENT_DATA_RESET:
        break;
    }
}

void DataRecorder::record() {
    SensorValue accel;
    SensorValue gyro;

    M5.Mpu6886.getAccelData(accel.getXPtr(), accel.getYPtr(), accel.getZPtr());
    _avgAccel += accel;

    M5.Mpu6886.getGyroData(gyro.getXPtr(), gyro.getYPtr(), gyro.getZPtr());
    _avgGyro += gyro;

    _avgCounter ++;
    if ( _avgCounter == 100 ) {
        _accel = _avgAccel / _avgCounter;
        _gyro = _avgGyro / _avgCounter;
        _avgAccel = 0.0f;
        _avgGyro = 0.0f;
        _avgCounter = 0;
        _dataStore.add(_accel, _gyro);
        eventQueue.push(EVENT_DATA_ON_CHANGE);
    }
}

void DataRecorder::loop() {
    switch (_status) {
        case dataRecord:
            record();
        break;
    }
}
