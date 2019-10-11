/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/src/PortAudio/StreamParam.cpp
*/

#include "StreamParam.hpp"

StreamParam::StreamParam(StreamType type)
{
    const PaDeviceInfo *info;

    if (type == StreamType::INPUT_STREAM)
        _param.device = Pa_GetDefaultInputDevice();
    else
        _param.device = Pa_GetDefaultOutputDevice();
    if (_param.device == paNoDevice) {
        std::cerr << "No default device found" << std::endl;
        exit(84);
    }
    info = Pa_GetDeviceInfo(_param.device);
    if (type == StreamType::INPUT_STREAM) {
        _param.channelCount = 2;
        _param.suggestedLatency = info->defaultLowInputLatency;
    } else {
        _param.channelCount = 2;
        _param.suggestedLatency = info->defaultLowOutputLatency;
    }
    _param.sampleFormat = paInt16;
    _param.hostApiSpecificStreamInfo = nullptr;
}

StreamParam::~StreamParam()
{
}

PaStreamParameters &StreamParam::getStreamParameters()
{
    return _param;
}