#include "StreamReaderWriter.h"



StreamReader::StreamReader(Stream *stream)
    : _stream(stream),
    _buffer(NULL),
    _bufferLength(0)
{

};

StreamReader::~StreamReader(){
    if ( _buffer ) {
        free(_buffer);
        _bufferLength = 0;
        _buffer = NULL;
    }
}

uint8_t StreamReader::readByte() {
    uint8_t value;
    if ( !_stream) {
        return 0;
    }
    _stream->readBytes( &value, sizeof(uint8_t));
    return value;
}

uint16_t StreamReader::readWord() {
    uint16_t value;
    if ( !_stream) {
        return 0;
    }
    _stream->readBytes( (uint8_t *) &value, sizeof(uint16_t));
    return value;
}

uint32_t StreamReader::readDWord() {
    uint32_t value;
    if ( !_stream) {
        return 0;
    }
    _stream->readBytes( (uint8_t *) &value, sizeof(uint32_t));
    return value;
}

unsigned int StreamReader::readInt() {
    unsigned int value;
    if ( !_stream) {
        return 0;
    }
    _stream->readBytes((uint8_t *) &value, sizeof(unsigned int));
    return value;
}

String StreamReader::readString(int maxLength) {
    String value;
    char *buffer = NULL;
    if ( !_stream) {
        return "";
    }
    unsigned int length = readInt();
    if ( length > 0  && ( maxLength == 0 || length < maxLength ) ) {
        if ( length + 1 > _bufferLength ) {
            _bufferLength = length + 1;
			_buffer = (char *) realloc(_buffer, _bufferLength);
        }
        if ( _buffer ) {
            _stream->readBytes(_buffer, length);
            _buffer[length] = 0;
            value = _buffer;
        }
    }
    return value;
}

double StreamReader::readDouble() {
    double value;
    if ( !_stream) {
        return 0;
    }
    _stream->readBytes((uint8_t *) &value, sizeof(double));
    return value;
}

float StreamReader::readFloat() {
    double value;
    if ( !_stream) {
        return 0;
    }
    _stream->readBytes((uint8_t *) &value, sizeof(float));
    return value;
}

unsigned long StreamReader::readLong() {
    unsigned long value;
    if ( !_stream) {
        return 0;
    }
    _stream->readBytes((uint8_t *) &value, sizeof(unsigned long));
    return value;
}

StreamWriter::StreamWriter(Stream *stream)
    : _stream(stream)
{

};

StreamWriter::~StreamWriter() {
}


size_t StreamWriter::writeByte(uint8_t value) {
    if ( !_stream) {
        return 0;
    }
        return _stream->write(&value, sizeof(uint8_t));
    }

size_t StreamWriter::writeWord(uint16_t value) {
    if ( !_stream) {
        return 0;
    }
    return _stream->write((uint8_t *) &value, sizeof(uint16_t));
}

size_t StreamWriter::writeDWord(uint32_t value) {
    if ( !_stream) {
        return 0;
    }
    return _stream->write((uint8_t *) &value, sizeof(uint32_t));
}

size_t StreamWriter::writeInt(unsigned int value) {
    if ( !_stream) {
        return 0;
    }
    return _stream->write((uint8_t *)&value, sizeof(unsigned int));
}

size_t StreamWriter::writeString(String value) {
    if ( !_stream) {
        return 0;
    }
    size_t writeLength;
    writeLength = write(value.length());
    writeLength += _stream->write(value.c_str(), value.length());
    return writeLength;
}

size_t StreamWriter::writeDouble(double value) {
    if ( !_stream) {
        return 0;
    }
    return _stream->write((uint8_t *)&value, sizeof(double));
}

size_t StreamWriter::writeFloat(float value) {
    if ( !_stream) {
        return 0;
    }
    return _stream->write((uint8_t *)&value, sizeof(float));
}

size_t StreamWriter::writeLong(unsigned long value) {
    if ( !_stream) {
        return 0;
    }
    return _stream->write((uint8_t *)&value, sizeof(unsigned long));
}
