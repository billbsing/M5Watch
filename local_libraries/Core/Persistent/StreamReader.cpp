/*

    StreamReader

*/

#include "StreamReader.h"

StreamReader::StreamReader(Stream *stream):
_stream(stream),
_buffer(NULL) {

}
StreamReader::~StreamReader() {
    clearBuffer();
}

uint8_t StreamReader::readByte() {
    uint8_t value = 0;
    _stream->readBytes((uint8_t *) &value, sizeof(uint8_t));
    return value;
}

uint16_t StreamReader::readWord() {
    uint16_t value;
    _stream->readBytes( (uint8_t *) &value, sizeof(uint16_t));
    return value;
}

uint32_t StreamReader::readDWord() {
    uint32_t value;
    _stream->readBytes( (uint8_t *) &value, sizeof(uint32_t));
    return value;
}

float StreamReader::readFloat() {
    float value;
    _stream->readBytes( (uint8_t *) &value, sizeof(float));
    return value;
}

float StreamReader::readDouble() {
    double value;
    _stream->readBytes( (uint8_t *) &value, sizeof(double));
    return value;
}

void StreamReader::clearBuffer() {
    if (_buffer) {
        free(_buffer);
        _buffer = NULL;
    }
}
char *StreamReader::readString() {
    uint32_t length = 0;
    length = readDWord();
    clearBuffer();
    if  ( length > 0) {
        _buffer = (char *) malloc(length + 1);
        _stream->readBytes( (char *) _buffer, length);
        _buffer[length] = 0;
    }
    return _buffer;
}
