/*

    StreamReader

*/

#ifndef STREAM_READER_H
#define STREAM_READER_H

#include <Stream.h>

class StreamReader
{
public:

    StreamReader(Stream *stream);
    ~StreamReader();
    
    uint8_t readByte();
    uint16_t readWord();
    uint32_t readDWord();
    float readFloat();
    float readDouble();
    char *readString();

    void clearBuffer();

private:
    Stream *_stream;
    char *_buffer;
};


#endif          // STREAM_READER_H
