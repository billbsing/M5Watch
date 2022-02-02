#ifndef PERSISTENT_H
#define PERSISTENT_H


#include "../core.h"
#include "StreamReader.h"
#include "StreamWriter.h"

class PersistentFile
{
public:
    boolean readFromFile(String filename);
    boolean writeToFile(String filename);
    boolean writeToFile(String filename, String mode);

    virtual void readFromStream(Stream *stream) = 0;
    virtual size_t writeToStream(Stream *stream) const = 0;

};


#endif          // PERSISTENT_H
