/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/include/PortAudio/StreamParam.hpp
*/

#ifndef STREAMPARAM_HPP
#define STREAMPARAM_HPP

#include <iostream>
#include "portaudio.h"

enum StreamType {
    INPUT_STREAM,
    OUTPUT_STREAM
};

class StreamParam
{
    public:
        StreamParam(StreamType type);
        ~StreamParam();

        PaStreamParameters &getStreamParameters();

    private:
        PaError _err;
        PaStreamParameters _param;
};

#endif