/*

    DataStore

*/

#include <TimeLib.h>
#include "DataStore.h"
#include "DataStoreItem.h"


DataStore::DataStore() {

}

void DataStore::addItem(DataItem &accel, DataItem &gyro) {
    DataStoreItem item;
    item.setAccel(accel);
    item.setGyro(gyro);
    item.setMillis(millis());
    item.setTime(now());
}

// PersistentFile
void DataStore::readFromStream(Stream *stream) {

}
size_t DataStore::writeToStream(Stream *stream) {

}
