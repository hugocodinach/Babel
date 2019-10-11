/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/src/Opus/Decoder.cpp
*/

#include "Decoder.hpp"

Decoder::Decoder(double sampleRate)
{
    _decoder = opus_decoder_create(sampleRate, 2, &_error);

    if (_error != OPUS_OK) {
        std::cerr << opus_strerror(_error) << std::endl;
        exit(84);
    }
}

Decoder::~Decoder()
{
    opus_decoder_destroy(_decoder);
}

opus_int32 Decoder::decode(int frameSize, opus_int32 length, std::vector<unsigned char> encoded,
std::vector<unsigned short> &decoded)
{
    _error = opus_decode(_decoder, encoded.data(), length,
    reinterpret_cast<opus_int16*>(decoded.data()), frameSize, 0);

    if (_error < OPUS_OK) {
        std::cerr << opus_strerror(_error) << std::endl;
        exit(84);
    }

    return _error;
}