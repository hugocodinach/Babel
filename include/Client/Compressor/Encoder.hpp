/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/include/Opus/Encoder.hpp
*/

#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include <iostream>
#include <vector>
#include "opus.h"

class Encoder
{
    public:
        Encoder(double sampleRate);
        ~Encoder();

        opus_int32 encode(int frameSize, std::vector<unsigned short> captured,
        std::vector<unsigned char> &encoded);

    private:
        int _error;
        OpusEncoder *_encoder;
};

#endif