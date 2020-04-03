/*

    DataRecorder.h

*/

#ifndef DATA_RECORDER_H
#define DATA_RECORDER_H

#include <M5StickC.h>
#include "DataStore.h"

typedef enum {
    dataIdle = 0,
    dataRecord,
    dataUpload
} DataStatus;

class DataRecorder
{
public:
    DataRecorder(String filename);

    DataItem &getGyro() { return _gyro; }
    DataItem &getAccel() { return _accel; }
    DataStatus getStatus() { return _status; }
    void loop();

private:
    DataItem _avgGyro;
    DataItem _avgAccel;

    DataItem _gyro;
    DataItem _accel;

    uint16_t _avgCounter;
    DataStatus _status;
    String _filename;

    DataStore _dataStore;

};



#endif                  // DATA_RECORDER_H
