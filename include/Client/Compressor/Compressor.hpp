/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/include/Compressor/Compressor.hpp
*/

#ifndef _COMPRESSOR_HPP_
#define _COMPRESSOR_HPP_

#include "Decoder.hpp"
#include "Encoder.hpp"

class Compressor
{
    public:
        Compressor(double sampleRate, double framePerBuffer);
        ~Compressor();

        Decoder *getDecoder();
        Encoder *getEncoder();
        std::vector<unsigned char> &getData();

    private:
        double _sampleRate;
        Decoder *_decoder;
        Encoder *_encoder;
        std::vector<unsigned char> _data;
};

#endif