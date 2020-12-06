/*
** EPITECH PROJECT, 2020
** Babel client main
** File description:
** Where the program starts
*/

#pragma once

#include "portaudio.h"
#include <iostream>

namespace Babel {
	namespace Client {
		/**
		 * \brief Port-Audio encapsulation used to create and manage audio stream
		 */
		class AudioStream {
		public:
			AudioStream();
			~AudioStream();
			bool createStream(double sampleRate, unsigned long framesPerBuffer, PaStreamCallback* callback, void* data);
			bool startStream();
			bool stopStream();
			std::string getInputDeviceName() const;
			std::string getOutputDeviceName() const;
		private:
			PaError _err;
			PaStream* _stream;
			bool _isStreaming;
		};
	}
}