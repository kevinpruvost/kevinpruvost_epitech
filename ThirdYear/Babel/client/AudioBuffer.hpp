/*
** EPITECH PROJECT, 2020
** Babel client main
** File description:
** Where the program starts
*/

#pragma once

#define FRAMES_PER_BUFFER (480)
#define SAMPLE_RATE (48000)
#define BUFFER_SIZE (FRAMES_PER_BUFFER * 20)
#define SAMPLE_TYPE uint16_t

#include <vector>
#include <mutex>
#include <iostream>

namespace Babel {
	namespace Client {
		/**
		 * \brief Manage an audio buffer
		 */
		class AudioBuffer {
		public:
			AudioBuffer();
			~AudioBuffer();
			void writeBuffer(const SAMPLE_TYPE*data, unsigned int dataSize);
			std::vector<SAMPLE_TYPE> readBuffer();
			void clearBuffer();
		private:
			SAMPLE_TYPE *_buffer;
			unsigned int _readIndex;
			unsigned int _writeIndex;
			std::mutex _readIndexMutex;
			std::mutex _writeIndexMutex;
		};
	}
}