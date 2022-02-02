
#include <FS.h>
#include <SPIFFS.h>
#include "PersistentFile.h"


boolean PersistentFile::readFromFile(String filename) {
    uint8_t fileVersion;
    File file = SPIFFS.open(filename.c_str(), "r");
    if ( file ) {
      readFromStream(&file);
      file.close();
    }
    return true;
}
boolean PersistentFile::writeToFile(String filename) {
    return writeToFile(filename, "w+");
}

boolean PersistentFile::writeToFile(String filename, String mode) {
    File file = SPIFFS.open(filename.c_str(), mode.c_str());
    if ( file ) {
      writeToStream(&file);
      file.close();
      return true;
    }
    return false;
}
