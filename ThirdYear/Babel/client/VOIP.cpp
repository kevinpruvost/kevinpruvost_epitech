/*
** EPITECH PROJECT, 2020
** Babel client main
** File description:
** Where the program starts
*/

#include "VOIP.hpp"

Babel::Client::VOIP::VOIP() :
    _socket(new QUdpSocket(nullptr)),
    _networkAudioThread(nullptr),
    _isInCall(false),
    _compressor(SAMPLE_RATE, 1),
    _audioBuffers(),
    _targetPort(0),
    _ownPort(0),
    _senderPort(0)
{
    _audioBuffers._isMicOn = true;
}

Babel::Client::VOIP::~VOIP()
{
    _isInCall = false;
}

/**
 * \brief Set the IP and PORT where socket will listen.
 * \param string ip
 * \param unsigned int port
 */
void Babel::Client::VOIP::setIPandPort(const std::string& ip, unsigned int port)
{
    if (_socket->state() == QAbstractSocket::BoundState) {
        _socket->disconnectFromHost();
    }
    _ownIp.setAddress(Babel::Client::UserInterface::QStringFromStdString(ip));
    if (_ownPort == 0)
        _socket->bind(_ownIp);
    else
        _socket->bind(_ownIp, (quint16)port);
    _ownPort = _socket->localPort();
}

/**
 * \brief set IP and PORT where socket will send audio.
 * \param string ip
 * \param unsigned int port
 */
void Babel::Client::VOIP::setTargetIPandPort(const std::string& ip, unsigned int port)
{
    _targetIp.setAddress(Babel::Client::UserInterface::QStringFromStdString(ip));
    _targetPort = (quint16)port;
}

/**
 * \brief Return socket's port.
 * \return quint16
 */
quint16 Babel::Client::VOIP::getPort() const
{
    return (_ownPort);
}

/**
 * \brief Return target socket's port.
 * \return quint16 port
 */
quint16 Babel::Client::VOIP::getTargetPort() const
{
    return (_targetPort);
}

/**
 * \brief Send audio on the socket.
 * \param const SAMPLE_TYPE* frames
 */
void Babel::Client::VOIP::sendAudio(const SAMPLE_TYPE* frames)
{
    QByteArray data;

    data.append((char*)frames, sizeof(SAMPLE_TYPE) * FRAMES_PER_BUFFER);
    _socket->writeDatagram(data, data.size(), _targetIp, _targetPort);
    _socket->waitForBytesWritten();
}

/**
 * \brief Send audio on the socket.
 * \param const std::vector<SAMPLE_TYPE> frames
 */
void Babel::Client::VOIP::sendAudio(const std::vector<SAMPLE_TYPE> frames)
{
    QByteArray data;

    data.append((char*)frames.data(), sizeof(SAMPLE_TYPE) * (unsigned int)frames.size());
    _socket->writeDatagram(data, data.size(), _targetIp, _targetPort);
    _socket->waitForBytesWritten();
}

/**
 * \brief Read audio from the socket.
 * \return QByteArray datagram
 */
QByteArray& Babel::Client::VOIP::readSocketAudio()
{
    if (_socket->hasPendingDatagrams()) {
        _datagram.resize(_socket->pendingDatagramSize());
        _socket->readDatagram(_datagram.data(), _datagram.size(), &_sender, &_senderPort);
        if (_targetIp.isNull()) {
            _targetIp = _sender;
            _targetPort = _senderPort;
        }
    } else {
        _datagram.resize(0);
    }
    return (_datagram);
}

/**
 * \brief Port-Audio callback function used to play & receive audio.
 * \return 0 to continue 1 to stop the stream
 */
int streamCallBack(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* data)
{
    SAMPLE_TYPE* input = (SAMPLE_TYPE*)inputBuffer;
    SAMPLE_TYPE* output = (SAMPLE_TYPE*)outputBuffer;
    std::vector<SAMPLE_TYPE> outSocketAudio;
    Babel::Client::VOIP::AudioBuffers* audioBuffers = (Babel::Client::VOIP::AudioBuffers*) data;
    size_t len;

    outSocketAudio = audioBuffers->outputBuffer.readBuffer();
    len = outSocketAudio.size();
    if (len == 0) {
        memset(output, 0, framesPerBuffer * sizeof(SAMPLE_TYPE));
    } else {
        for (size_t i = 0; i < FRAMES_PER_BUFFER && i < len; ++i)
            output[i] = outSocketAudio[i];
    }
    if (input && audioBuffers->_isMicOn)
        audioBuffers->inputBuffer.writeBuffer(input, framesPerBuffer);
    return (paContinue);
}

/**
 * \brief Main loop running in a thread sending and receiving audio.
 */
void Babel::Client::VOIP::audioStream()
{
    if (!_audioStream.createStream((double)SAMPLE_RATE, (unsigned long)FRAMES_PER_BUFFER, streamCallBack, &_audioBuffers))
        return;
    if (!_audioStream.startStream())
        return;

    std::vector<SAMPLE_TYPE> microphoneRawAudio;
    std::vector<SAMPLE_TYPE> encoded;
    std::vector<SAMPLE_TYPE> decoded;

    QByteArray datagram;
    unsigned int datagramLen;

    while (_isInCall) {
        microphoneRawAudio = _audioBuffers.inputBuffer.readBuffer();
        if (microphoneRawAudio.size() > 0) {
            encoded = _compressor.encode(microphoneRawAudio);
            sendAudio(encoded.data());
        }
        datagram = readSocketAudio();
        datagramLen = datagram.size();

        if (datagramLen > 0) {
            decoded = _compressor.decode((SAMPLE_TYPE*)datagram.data(), datagramLen / sizeof(SAMPLE_TYPE));
            _audioBuffers.outputBuffer.writeBuffer((SAMPLE_TYPE*)decoded.data(), (unsigned int)decoded.size());
        }
    }
    _audioStream.stopStream();
    std::cout << "VOIP: Call terminated." << std::endl;
}

/**
 * \brief Start audioStream() in a thread.
 */
void Babel::Client::VOIP::startStream()
{
    if (_isInCall) {
        std::cerr << "Error: already in call" << std::endl;
        return;
    }
    if (_ownIp.isNull() || _ownPort == 0 || _targetIp.isNull() || _targetPort == 0) {
        std::cerr << "Error: VOIP is no bind or does not have target." << std::endl;
        return;
    }
    std::cout << "VOIP: starting stream using: " << _audioStream.getInputDeviceName() << " as microphone and " << _audioStream.getOutputDeviceName() << " as speaker." << std::endl;
    _audioBuffers._isMicOn = true;
    _isInCall = true;
    _networkAudioThread = new std::thread([this]() { this->audioStream(); });
}

/**
 * \brief Stop the audio thread
 */
void Babel::Client::VOIP::stopStream()
{
    _isInCall = false;
    _audioBuffers.inputBuffer.clearBuffer();
    _audioBuffers.outputBuffer.clearBuffer();
}

/**
 * \brief Enable/Disable microphone
 */
void Babel::Client::VOIP::setMicrophoneState(bool state)
{
    _audioBuffers._isMicOn = state;
}

/**
 * \brief Returns the microphone state
 * \return bool isMicOn
 */
bool Babel::Client::VOIP::getMicrophoneState() const
{
    return (_audioBuffers._isMicOn);
}

/**
 * \brief Return TRUE if receiving audio.
 */
bool Babel::Client::VOIP::isReceivingAudio() const
{
    return (true);
}