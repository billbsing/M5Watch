
#ifndef STREAM_READ_WRITE_H
#define STREAM_READ_WRITE_H

#include <Arduino.h>

class StreamReader
{
public:
    StreamReader(Stream *stream);
    ~StreamReader();

    uint8_t readByte();
    char readChar() { return readByte(); }
    uint16_t readWord();
    uint32_t readDWord();
    unsigned int readInt();
    String readString(int maxLength = 0);
    double readDouble();
    float readFloat();
    unsigned long readLong();

protected:
    Stream *_stream;
    char *_buffer;
    int _bufferLength;
};


class StreamWriter
{
public:
    StreamWriter(Stream *stream);
    ~StreamWriter();

    size_t writeByte(uint8_t value);
    size_t writeChar(char value) { writeByte(value); }
    size_t writeWord(uint16_t value);
    size_t writeDWord(uint32_t value);
    size_t writeInt(unsigned int value);
    size_t writeLong(unsigned long value);
    size_t writeString(String value);
    size_t writeDouble(double value);
    size_t writeFloat(float value);

    size_t write(uint8_t value)  { return writeByte(value); }
    size_t write(char value)  { return writeChar(value); }
    size_t write(uint16_t value)  { return writeWord(value); }
//    size_t write(uint32_t value)  { return writeDWord(value); }
    size_t write(unsigned int value) { return writeInt(value); }
    size_t write(unsigned long value) { return writeLong(value); }
    size_t write(String value) { return writeString(value); }
    size_t write(double value) { return writeDouble(value); }
    size_t write(float value) { return writeFloat(value); }

protected:
    Stream *_stream;
};





#endif
