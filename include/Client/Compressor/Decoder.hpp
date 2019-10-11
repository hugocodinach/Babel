/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/include/Opus/Decoder.hpp
*/

#ifndef _DECODER_HPP_
#define _DECODER_HPP_

#include <iostream>
#include <vector>
#include "opus.h"

class Decoder
{
    public:
        Decoder(double sampleRate);
        ~Decoder();

        opus_int32 decode(int frameSize, opus_int32 length,
        std::vector<unsigned char> encoded, std::vector<unsigned short> &decoded);

    private:
        int _error;
        OpusDecoder *_decoder;
};

#endif