/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/include/Stream.hpp
*/

#ifndef _STREAM_HPP_
#define _STREAM_HPP_

#include <iostream>
#include <vector>
#include "StreamParam.hpp"
#include "portaudio.h"

class Stream
{
    public:
        Stream(int sampleRate, int framePerBuffer, StreamType type);
        ~Stream();

        void startStream();
        void stopStream();
        bool isStreamActive();
        bool isStreamStopped();
        void readStream();
        void writeStream();
        std::vector<unsigned short> &getData();

    private:
        PaError _err;
        PaStream *_stream;
        StreamParam *_param;
        int _sampleRate;
        int _framePerBuffer;
        std::vector<unsigned short> _data;
};

#endif