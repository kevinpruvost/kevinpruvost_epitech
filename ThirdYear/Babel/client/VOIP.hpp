/*
** EPITECH PROJECT, 2020
** Babel client main
** File description:
** Where the program starts
*/

#pragma once

#include <thread>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <QUdpSocket>

// PORT AUDIO SETTINGS ARE STORED IN AudioBuffer.hpp

#include "AudioStream.hpp"
#include "Compressor.hpp"
#include "UI/NewConversionFromStdStringToQString.hpp"

namespace Babel {
	namespace Client {
		/**
		 * \brief Manage audio and udp communications
		 */
		class VOIP {
		public:
			/**
			 * \brief Contain audio buffers (passed as argument to the PortAudio callback function)
			 */
			struct AudioBuffers {
				AudioBuffer inputBuffer;
				AudioBuffer outputBuffer;
				bool _isMicOn;
			};
		public:
			VOIP();
			virtual ~VOIP();
			void setIPandPort(const std::string& ip, unsigned int port);
			void setTargetIPandPort(const std::string& ip, unsigned int port);
			quint16 getPort() const;
			quint16 getTargetPort() const;
			void startStream();
			void stopStream();
			void setMicrophoneState(bool state);
			bool getMicrophoneState() const;
			bool isReceivingAudio() const;
		private:
			void audioStream(void);
			void sendAudio(const SAMPLE_TYPE* frames);
			void sendAudio(const std::vector<SAMPLE_TYPE> frames);
			QByteArray& readSocketAudio();
		private:
			QUdpSocket* _socket;
			QHostAddress _ownIp;
			quint16 _ownPort;
			QHostAddress _targetIp;
			quint16	_targetPort;
			QByteArray _datagram;
			QHostAddress _sender;
			quint16	_senderPort;

			std::thread* _networkAudioThread;
			bool _isInCall;
			AudioBuffers _audioBuffers;
			Compressor _compressor;
			AudioStream _audioStream;
		};
	}
}

int streamCallBack(const void* input, void* output,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void* audioBuffers);