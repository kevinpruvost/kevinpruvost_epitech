/*
** EPITECH PROJECT, 2020
** Babel client main
** File description:
** Where the program starts
*/

#include "AudioBuffer.hpp"

#include <string.h>

Babel::Client::AudioBuffer::AudioBuffer() : _readIndex(0), _writeIndex(0), _buffer((SAMPLE_TYPE*)malloc(sizeof(SAMPLE_TYPE) * BUFFER_SIZE))
{
}

Babel::Client::AudioBuffer::~AudioBuffer()
{
    if (_buffer)
        free(_buffer);
}

/**
 * \brief Write audio in the buffer
 * \param const SAMPLE_TYPE* data
 * \param unsigned int dataSize
 */
void Babel::Client::AudioBuffer::writeBuffer(const SAMPLE_TYPE* data, unsigned int dataSize)
{
    unsigned int tmpWriteIndex;

    _writeIndexMutex.lock();
    tmpWriteIndex = _writeIndex;
    _writeIndexMutex.unlock();
    for (unsigned int i = 0; i < dataSize; ++i) {
        _buffer[tmpWriteIndex] = data[i];
        tmpWriteIndex = (tmpWriteIndex + 1) % BUFFER_SIZE;
    }
    _writeIndexMutex.lock();
    _writeIndex = tmpWriteIndex;
    _writeIndexMutex.unlock();
}

/**
 * \brief Read audio from the buffer
 * \return std::vector<SAMPLE_TYPE> audio sample
 */
std::vector<SAMPLE_TYPE> Babel::Client::AudioBuffer::readBuffer()
{
    std::vector<SAMPLE_TYPE> data;
    unsigned int tmpReadIndex;
    unsigned int tmpWriteIndex;

    _readIndexMutex.lock();
    tmpReadIndex = _readIndex;
    _readIndexMutex.unlock();
    _writeIndexMutex.lock();
    tmpWriteIndex = _writeIndex;
    _writeIndexMutex.unlock();
    if (tmpWriteIndex != tmpReadIndex) {
        for (unsigned int i = 0; i < FRAMES_PER_BUFFER; ++i) {
            data.push_back(_buffer[tmpReadIndex]);
            tmpReadIndex = (tmpReadIndex + 1) % BUFFER_SIZE;
        }
    }
    _readIndexMutex.lock();
    _readIndex = tmpReadIndex;
    _readIndexMutex.unlock();
    return (data);
}

/**
 * \brief Clear the buffer
 */
void Babel::Client::AudioBuffer::clearBuffer()
{
    _readIndexMutex.lock();
    _writeIndexMutex.lock();
    _readIndex = 0;
    _writeIndex = 0;
    memset(_buffer, 0, sizeof(SAMPLE_TYPE) * BUFFER_SIZE);
    _readIndexMutex.unlock();
    _writeIndexMutex.unlock();
}