/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/src/Compressor/Compressor.cpp
*/

#include "Compressor.hpp"

Compressor::Compressor(double sampleRate, double framePerBuffer)
{
    _sampleRate = sampleRate;
    _decoder = new Decoder(sampleRate);
    _encoder = new Encoder(sampleRate);
    _data.resize(framePerBuffer * 4);
}

Compressor::~Compressor()
{
    if (_decoder)
        delete _decoder;
    if (_encoder)
        delete _encoder;
}

Decoder *Compressor::getDecoder()
{
    return _decoder;
}

Encoder *Compressor::getEncoder()
{
    return _encoder;
}

std::vector<unsigned char> &Compressor::getData()
{
    return _data;
}