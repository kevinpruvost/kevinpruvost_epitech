/*
** EPITECH PROJECT, 2020
** Babel client main
** File description:
** Where the program starts
*/

#pragma once

#include <opus/opus.h>
#include <iostream>
#include <vector>
#include <stdint.h>

#include "AudioBuffer.hpp"

namespace Babel {
	namespace Client {
		/**
		 * \brief Encapsulation of OPUS for audio encoding/decoding
		 */
		class Compressor {
		public:
			Compressor(uint32_t sampleRate, uint32_t channel);
			~Compressor();

			std::vector<SAMPLE_TYPE> encode(std::vector<SAMPLE_TYPE> sample);
			std::vector<SAMPLE_TYPE> decode(std::vector<SAMPLE_TYPE> encoded);
			std::vector<SAMPLE_TYPE> decode(SAMPLE_TYPE* encoded, unsigned int size);
		private:
			OpusEncoder* _encoder;
			OpusDecoder* _decoder;
		};
	}
}