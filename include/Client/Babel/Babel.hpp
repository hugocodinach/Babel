/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/include/Babel/Babel.hpp
*/

#ifndef _BABEL_HPP_
#define _BABEL_HPP_

#include "Compressor.hpp"
#include "Audio.hpp"
#include "Stream.hpp"
#include "QtBabel.hpp"
#include "WindowProgram.hpp"
#include <vector>
#include <boost/algorithm/string.hpp>

typedef struct streamOther_s {
    std::string ip;
    Stream * streamout;
} streamOther_t;

class Babel
{
    public:
        Babel(int ac, char **av, int sampleRate, int framesPerBuffer);
        ~Babel();

        Audio *getAudio();
        Stream *getStreamIn();
        Stream * getStreamOut();
        Compressor *getCompressor();
        QtBabel *getQtBabel();
        int _framesPerBuffer;

    private:
        int _sampleRate;
        Audio *_audio;
        Stream *_streamIn;
        Stream *_streamOut;
        Compressor *_compressor;
        QtBabel *_qt;
        WindowProgram *_win;
        
};

#endif