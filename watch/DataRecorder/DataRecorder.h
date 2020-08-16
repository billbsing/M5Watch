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
    dataUploadStart,
    dataUpload
} DataStatus;

class DataStore;

class DataRecorder
{
public:
    DataRecorder(String filename, IPAddress uploadServer, uint16_t uploadPort);

    SensorValue &getGyro() { return _gyro; }
    SensorValue &getAccel() { return _accel; }
    DataStatus getStatus() { return _status; }

    const DataStoreHeader& getStoreHeader() const { return _dataStore.getHeader(); }
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
    IPAddress _uploadServer;
    uint16_t _uploadPort;

    DataStore _dataStore;

};



#endif                  // DATA_RECORDER_H
