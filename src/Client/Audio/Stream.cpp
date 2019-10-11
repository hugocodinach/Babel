/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/src/Stream.cpp
*/

#include "Stream.hpp"

Stream::Stream(int sampleRate, int framePerBuffer, StreamType type)
{
    _sampleRate = sampleRate;
    _framePerBuffer = framePerBuffer;
    _param = new StreamParam(type);
    _data.resize(framePerBuffer * 4, 0);

    if (type == StreamType::INPUT_STREAM) {
        _err = Pa_OpenStream(
            &_stream,
            &_param->getStreamParameters(),
            nullptr,
            sampleRate,
            framePerBuffer,
            paClipOff,
            nullptr,
            nullptr);
    } else {
        _err = Pa_OpenStream(
            &_stream,
            nullptr,
            &_param->getStreamParameters(),
            sampleRate,
            framePerBuffer,
            paClipOff,
            nullptr,
            nullptr);
    }

    if (_err != paNoError) {
        std::cerr << "Stream error: " << Pa_GetErrorText(_err) << std::endl;
        exit(84);
    }
}

Stream::~Stream()
{
    _err = Pa_CloseStream(_stream);

    if (_err != paNoError) {
        std::cerr << "Stream error: " << Pa_GetErrorText(_err) << std::endl;
        exit(84);
    }
    delete _param;
}

void Stream::startStream()
{
    _err = Pa_StartStream(_stream);

    if (_err != paNoError) {
        std::cerr << "Stream error: " << Pa_GetErrorText(_err) << std::endl;
        exit(84);
    }
}

void Stream::stopStream()
{
    _err = Pa_StopStream(_stream);

    if (_err != paNoError) {
        std::cerr << "Stream error: " << Pa_GetErrorText(_err) << std::endl;
        exit(84);
    }
}

bool Stream::isStreamActive()
{
    _err = Pa_IsStreamActive(_stream);

    if (_err == 1) {
        return true;
    } else if (_err == 0) {
        return false;
    }
    std::cerr << "Stream error: " << Pa_GetErrorText(_err) << std::endl;
    exit(84);
}

bool Stream::isStreamStopped()
{
    _err = Pa_IsStreamStopped(_stream);

    if (_err == 1) {
        return true;
    } else if (_err == 0) {
        return false;
    }
    std::cerr << "Stream error: " << Pa_GetErrorText(_err) << std::endl;
    exit(84);
}

void Stream::readStream()
{
    _err = Pa_ReadStream(_stream, _data.data(), _framePerBuffer);

    if (_err != paNoError) {
        std::cerr << "Stream error: " << Pa_GetErrorText(_err) << std::endl;
    }
}

void Stream::writeStream()
{
    _err = Pa_WriteStream(_stream, _data.data(), _framePerBuffer);

    if (_err != paNoError) {
        std::cerr << "Stream error: " << Pa_GetErrorText(_err) << std::endl;
    }
}

std::vector<unsigned short> &Stream::getData()
{
    return _data;
}