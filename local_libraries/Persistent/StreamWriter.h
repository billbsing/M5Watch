/*

    StreamData

*/

#ifndef STREAM_WRITER_H
#define STREAM_WRITER_H

#include <Stream.h>

class StreamWriter
{
public:

    StreamWriter(Stream *stream);

    size_t writeByte(const uint8_t value);
    size_t writeWord(const uint16_t value);
    size_t writeDWord(const uint32_t value);
    size_t writeFloat(const float value);
    size_t writeFloat(const double value);
    size_t writeString(const String &value);

private:
    Stream *_stream;

};


#endif          // STREAM_WRITER_H
