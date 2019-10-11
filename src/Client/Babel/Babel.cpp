/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/src/Client/Babel/Babel.cpp
*/

#include "myudp.hpp"

Babel::Babel(int ac, char **av, int sampleRate, int framesPerBuffer)
{
    _audio = new Audio();
    _streamIn = new Stream(sampleRate, framesPerBuffer, StreamType::INPUT_STREAM);
    _streamOut = new Stream(sampleRate, framesPerBuffer, StreamType::OUTPUT_STREAM);
    _compressor = new Compressor(sampleRate, framesPerBuffer);
    _qt = new QtBabel(ac, av);
    _win = new WindowProgram(nullptr);
    _win->getClient()->_udp = new MyUDP(this);
	_framesPerBuffer = framesPerBuffer;
	_sampleRate = sampleRate;
}

Babel::~Babel()
{
    if (_streamIn)
        delete _streamIn;
    if (_audio)
        delete _audio;
    if (_compressor)
        delete _compressor;
    delete _qt;
    delete _win;
}

Audio *Babel::getAudio()
{
    return _audio;
}

Stream *Babel::getStreamIn()
{
    return _streamIn;
}

Stream *Babel::getStreamOut()
{
    return _streamOut;
}

Compressor *Babel::getCompressor()
{
    return _compressor;
}

QtBabel *Babel::getQtBabel()
{
    return _qt;
}