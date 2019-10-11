/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/src/Opus/Encoder.cpp
*/

#include "Encoder.hpp"

Encoder::Encoder(double sampleRate)
{
    _encoder = opus_encoder_create(sampleRate, 2, OPUS_APPLICATION_VOIP, &_error);

    if (_error != OPUS_OK) {
        std::cerr << opus_strerror(_error) << std::endl;
        exit(84);
    }
}

Encoder::~Encoder()
{
    opus_encoder_destroy(_encoder);
}

opus_int32 Encoder::encode(int frameSize, std::vector<unsigned short> captured,
std::vector<unsigned char> &encoded)
{
    _error = opus_encode(_encoder, reinterpret_cast<opus_int16 *const>(captured.data()),
    frameSize, encoded.data(), encoded.size());

    if (_error < OPUS_OK) {
        std::cerr << opus_strerror(_error) << std::endl;
        exit(84);
    }

    return _error;
}