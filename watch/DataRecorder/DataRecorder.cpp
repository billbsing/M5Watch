/*

    SwimLapCounter

*/

#include "M5Watch.h"
#include "DataRecorder.h"



DataRecorder::DataRecorder(String filename, IPAddress uploadServer, uint16_t uploadPort):
_avgCounter(0),
_status(dataIdle),
_dataStore(filename),
_uploadServer(uploadServer),
_uploadPort(uploadPort) {

}

void DataRecorder::processEvent(uint16_t eventId) {
    switch(eventId) {
        case EVENT_DATA_INIT:
            if ( _status == dataIdle) {
                _dataStore.readHeader();
            }
            eventQueue.push(EVENT_DATA_ON_CHANGE);
        break;
        case EVENT_DATA_START:
            _status = dataRecord;
            eventQueue.push(EVENT_DATA_ON_CHANGE);
        break;
        case EVENT_DATA_STOP:
            _status = dataIdle;
            eventQueue.push(EVENT_DATA_SAVE);
            eventQueue.push(EVENT_DATA_ON_CHANGE);
        break;
        case EVENT_DATA_UPLOAD:
            _status = dataUpload;
            // save any left over buffer to file
            if ( _dataStore.getBufferCount() > 0) {
                eventQueue.push(EVENT_DATA_SAVE);
                eventQueue.pushDelay(EVENT_DATA_UPLOAD_ITEM, 500);
            }
            else {
                eventQueue.push(EVENT_DATA_UPLOAD_ITEM);
            }
            eventQueue.push(EVENT_DATA_ON_CHANGE);
        break;
        case EVENT_DATA_DELETE:
            _dataStore.deleteFile();
            eventQueue.push(EVENT_DATA_ON_CHANGE);
        break;
        case EVENT_DATA_SAVE:
            _dataStore.saveBufferToFile();
            eventQueue.push(EVENT_DATA_ON_CHANGE);
        break;
        case EVENT_DATA_UPLOAD_ITEM:
            // send an item to the server
            if ( _dataStore.getHeader().getWaitForUploadCount() > 0) {
                _dataStore.uploadItem(_uploadServer, _uploadPort);
                eventQueue.pushDelay(EVENT_DATA_UPLOAD_ITEM, 100);
            }
            else {
                _status = dataIdle;
            }
            eventQueue.push(EVENT_DATA_ON_CHANGE);
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
        if ( _dataStore.isBufferFull()) {
            eventQueue.push(EVENT_DATA_SAVE);
        }
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
