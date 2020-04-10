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

    uint8_t readByte();
    uint16_t readWord();
    uint32_t readDWord();
    float readFloat();
    float readDouble();
    String readString();

private:
    Stream *_stream;
};


#endif          // STREAM_READER_H
