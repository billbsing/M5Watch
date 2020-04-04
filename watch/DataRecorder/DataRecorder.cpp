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

void DataRecorder::prcoessEvent(uint16_t eventId) {
        switch(eventId) {
            case EVENT_DATA_START:
                _status = dataRecord;
            break;
            case EVENT_DATA_STOP:
                _status = dataIdle;
            break;
            case EVENT_DATA_UPLOAD:
                _status = dataUpload;
            break;
            case EVENT_DATA_RESET:
            break;
        }
}

void DataRecorder::loop() {
    SensorValue gyro;
    SensorValue accel;

    M5.Mpu6886.getAccelData(accel.getXPtr(), accel.getYPtr(), accel.getZPtr());
    _avgAccel += accel;

    M5.Mpu6886.getGyroData(gyro.getXPtr(), gyro.getYPtr(), gyro.getZPtr());
    _avgGyro += gyro;

    _avgCounter ++;
    if ( _avgCounter == 100 ) {
        _accel = _avgAccel / _avgCounter;
        _gyro = _avgGyro / _avgCounter;

        _avgAccel = 0;
        _avgGyro = 0;
        _avgCounter = 0;
        if ( _status == dataRecord ) {
            _dataStore.add(_accel, _gyro);
        }
        eventQueue.push(EVENT_DATA_ON_CHANGE);
    }
}
