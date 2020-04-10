/*

    StreamReader

*/

#include "StreamReader.h"

StreamReader::StreamReader(Stream *stream):
_stream(stream) {

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

String StreamReader::readString() {
    String value;
    char *buffer;
    uint16_t length = readWord();
    if  ( length > 0) {
        buffer = (char *) malloc(length + 1);
        _stream->readBytes( (uint8_t *) buffer, length);
        buffer[length] = 0;
        value = String(buffer);
        free(buffer);
    }
    return value;
}
