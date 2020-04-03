/*

    DataStore


*/


#ifndef DATA_STORE_H
#define DATA_STORE_H

#include <PersistentFile.h>

typedef struct {
    float x;
    float y;
    float z;
} DataItem;

class DataStore: public PersistentFile
{
public:
    DataStore();

    void addItem(DataItem &accel, DataItem &gyro);
    // PersistentFile
    void readFromStream(Stream *stream);
    size_t writeToStream(Stream *stream);

private:

};


#endif                  // DATA_STORE_H
