/*

    DataRecorder.h

*/

#ifndef DATA_RECORDER_H
#define DATA_RECORDER_H

#include <M5StickC.h>

typedef struct {
    float x;
    float y;
    float z;
} DataItem;

class DataRecorder
{
public:
    DataRecorder();

    DataItem &getGyro() { return _gyro; }
    DataItem &getAccel() { return _accel; }

    void loop();

private:
    DataItem _avgGyro;
    DataItem _avgAccel;

    DataItem _gyro;
    DataItem _accel;

    uint16_t _avgCounter;

};



#endif                  // DATA_RECORDER_H
