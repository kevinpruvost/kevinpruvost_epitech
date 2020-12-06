/*
** EPITECH PROJECT, 2020
** Babel client main
** File description:
** Where the program starts
*/

#include "AudioStream.hpp"

Babel::Client::AudioStream::AudioStream() : _stream(NULL), _isStreaming(false)
{
	_err = Pa_Initialize();
	if (_err != paNoError) {
		std::cerr << "Error while initializing Port Audio.\n" << Pa_GetErrorText(_err) << std::endl;
	}
	std::cout << "Port-Audio successfully initialized." << std::endl;
}

Babel::Client::AudioStream::~AudioStream()
{
	if (_stream)
		_err = Pa_CloseStream(_stream);
	if (_err != paNoError)
		std::cerr << "Error while closing stream:\n" << Pa_GetErrorText(_err) << std::endl;
	_err = Pa_Terminate();
	if (_err != paNoError)
		std::cerr << "Error while terminating port audio:\n" << Pa_GetErrorText(_err) << std::endl;
	std::cout << "Terminating Port-Audio." << std::endl;
}

/**
 * \brief Open PortAudio stream with default parameters
 * \param Sample rate
 * \param Frames per buffer
 * \param PortAudio callBack function
 * \param Data passed to the CallBack function
 * \return A boolean saying if everything went okay
 */
bool Babel::Client::AudioStream::createStream(double sampleRate, unsigned long framesPerBuffer, PaStreamCallback*callback, void *data)
{
	if (_err != paNoError)
		return (false);
	if (_isStreaming) {
		std::cerr << "AudioStream error: Stream is already open" << std::endl;
		return (false);
	}
	if (_stream)
		return (true);
	_err = Pa_OpenDefaultStream(&_stream, 1, 1, paInt16, sampleRate, framesPerBuffer, callback, data);
	if (_err != paNoError) {
		std::cerr << "Error while opening stream.\n" << Pa_GetErrorText(_err) << std::endl;
		return (false);
	}
	return (true);
}

/**
 * \brief Start the stream (CallBack function will start being called)
 * \return A boolean saying if everything went okay
 */
bool Babel::Client::AudioStream::startStream()
{
	if (_err != paNoError)
		return (false);
	if (_isStreaming) {
		std::cerr << "AudioStream error: already streaming" << std::endl;
		return (false);
	}
	_err = Pa_StartStream(_stream);
	if (_err != paNoError) {
		std::cerr << "Error while starting stream.\n" << Pa_GetErrorText(_err) << std::endl;
		return (false);
	}
	_isStreaming = true;
	return (true);
}

/**
 * \brief Stop the stream (CallBack function will stop being called)
 * \return A boolean saying if everything went okay
 */
bool Babel::Client::AudioStream::stopStream()
{
	if (_err != paNoError)
		return (false);
	if (!_isStreaming) {
		std::cerr << "AudioStream error: trying to close non opened stream" << std::endl;
		return (false);
	}
	_err = Pa_StopStream(_stream);
	if (_err != paNoError) {
		std::cerr << "Error while closing stream.\n" << Pa_GetErrorText(_err) << std::endl;
		return (false);
	}
	_isStreaming = false;
	return (true);
}

/**
 * \brief A method that returns the default input device name
 * \return A string containing the audio device name
 */
std::string Babel::Client::AudioStream::getInputDeviceName() const
{
	PaDeviceIndex deviceIndex = Pa_GetDefaultInputDevice();
	if (deviceIndex == paNoDevice)
		return "";
	const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(deviceIndex);
	if (!deviceInfo)
		return "";
	return (std::string(deviceInfo->name));
}

/**
 * \brief A method that returns the default output device name
 * \return A string containing the audio device name
 */
std::string Babel::Client::AudioStream::getOutputDeviceName() const
{
	PaDeviceIndex deviceIndex = Pa_GetDefaultOutputDevice();
	if (deviceIndex == paNoDevice)
		return "";
	const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(deviceIndex);
	if (!deviceInfo)
		return "";
	return (std::string(deviceInfo->name));
}