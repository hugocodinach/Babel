/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/src/.cpp
*/

#include "Audio.hpp"
#include "portaudio.h"

Audio::Audio()
{
    PaError err = Pa_Initialize();

    if (err != paNoError) {
        std::cerr << "Audio error: " << Pa_GetErrorText(err) << std::endl;
        exit(84);
    }
}

Audio::~Audio()
{
    PaError err = Pa_Terminate();

    if(err != paNoError) {
        std::cerr << "Audio error: " << Pa_GetErrorText(err) << std::endl;
        exit(84);
    }
}

void Audio::pause(float second) const
{
    Pa_Sleep(second * 1000);
}