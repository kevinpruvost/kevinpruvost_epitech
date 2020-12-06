/*
** EPITECH PROJECT, 2020
** Babel client main
** File description:
** Where the program starts
*/

#include "Compressor.hpp"

Babel::Client::Compressor::Compressor(uint32_t sampleRate, uint32_t channel) : _encoder(nullptr), _decoder(nullptr)
{
	int opusError;
	_encoder = opus_encoder_create(sampleRate, channel, OPUS_APPLICATION_VOIP, &opusError);
	if (opusError != OPUS_OK)
		std::cerr << "Opus error: can't create encodre !: " << opusError << std::endl;
	_decoder = opus_decoder_create(sampleRate, channel, &opusError);
	if (opusError != OPUS_OK)
		std::cerr << "Opus error: can't create decoder !" << std::endl;
}

Babel::Client::Compressor::~Compressor()
{
	if (_encoder)
		opus_encoder_destroy(_encoder);
	if (_decoder)
		opus_decoder_destroy(_decoder);
}

/**
 * \brief Encode given audio sample
 * \param std::vector<SAMPLE_TYPE> sample
 * \return std::vector<SAMPLE_TYPE> encoded audio
 */
std::vector<SAMPLE_TYPE> Babel::Client::Compressor::encode(std::vector<SAMPLE_TYPE> sample)
{
	std::vector<SAMPLE_TYPE> encoded(sample.size());
	if (opus_encode(_encoder, (opus_int16 const*)sample.data(), (int)sample.size(), (unsigned char*)(encoded.data()), (int)sample.size()) < 0)
		std::cerr << "Opus error: error while encoding" << std::endl;
	return (encoded);
}

/**
 * \brief Decode given audio sample
 * \param std::vector<SAMPLE_TYPE> encoded audio
 * \return std::vector<SAMPLE_TYPE> decoded audio
 */
std::vector<SAMPLE_TYPE> Babel::Client::Compressor::decode(std::vector<SAMPLE_TYPE> encoded)
{
	std::vector<SAMPLE_TYPE> decoded(encoded.size());
	if (opus_decode(_decoder, (unsigned char*)encoded.data(), (int)encoded.size(), (opus_int16*)decoded.data(), (int)decoded.size(), 0) < 0)
		std::cerr << "Opus error: error while decoding" << std::endl;
	return (decoded);
}

/**
 * \brief Decode from a C array audio sample
 * \param SAMPLE_TYPE* encoded audio
 * \param unsigned int size of the audio sample
 * \return std::vector<SAMPLE_TYPE> decoded audio
 */
std::vector<SAMPLE_TYPE> Babel::Client::Compressor::decode(SAMPLE_TYPE *encoded, unsigned int size)
{
	std::vector<SAMPLE_TYPE> decoded(size);
	if (opus_decode(_decoder, (unsigned char*)encoded, (int)size, (opus_int16*)decoded.data(), (int)size, 0) < 0)
		std::cerr << "Opus error: error while decoding" << std::endl;
	return (decoded);
}