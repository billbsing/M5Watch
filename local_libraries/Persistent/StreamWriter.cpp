/*

    StreamWriter

*/

#include "StreamWriter.h"

StreamWriter::StreamWriter(Stream *stream):
_stream(stream) {

}

size_t StreamWriter::writeByte(const uint8_t value) {
    return _stream->write((uint8_t *) &value, sizeof(uint8_t));
}

size_t StreamWriter::writeWord(const uint16_t value) {
    return _stream->write((uint8_t *) &value, sizeof(uint16_t));
}

size_t StreamWriter::writeDWord(const uint32_t value) {
    return _stream->write((uint8_t *) &value, sizeof(uint32_t));
}

size_t StreamWriter::writeFloat(const float value) {
    return _stream->write((uint8_t *) &value, sizeof(float));
}

size_t StreamWriter::writeFloat(const double value) {
    return _stream->write((uint8_t *) &value, sizeof(double));
}

size_t StreamWriter::writeString(const String value) {
    size_t size;
    uint16_t length = value.length();
    writeWord(length);
    if ( length > 0) {
        size = _stream->write(value.c_str(), length);
    }
    return size;
}
