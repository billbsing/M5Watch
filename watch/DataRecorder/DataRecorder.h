/*

    DataRecorder.h

*/

#ifndef DATA_RECORDER_H
#define DATA_RECORDER_H

#include "SensorValue.h"
#include "DataStore.h"

typedef enum {
    dataIdle = 0,
    dataRecord,
    dataUpload
} DataStatus;

class DataStore;

class DataRecorder
{
public:
    DataRecorder(String filename);

    SensorValue &getGyro() { return _gyro; }
    SensorValue &getAccel() { return _accel; }
    DataStatus getStatus() { return _status; }
    void loop();
    void processEvent(uint16_t eventId);

protected:
    void record();
    
private:
    SensorValue _avgGyro;
    SensorValue _avgAccel;

    SensorValue _gyro;
    SensorValue _accel;

    uint16_t _avgCounter;
    DataStatus _status;
    String _filename;

    DataStore _dataStore;

};



#endif                  // DATA_RECORDER_H
