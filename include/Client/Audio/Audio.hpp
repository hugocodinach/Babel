/*
** EPITECH PROJECT, 2018
** SEC_crypto_2019
** File description:
** home/dorianrigal/Epitech/B5-Advanced_C++/CPP_babel_2019/include/Audio.hpp
*/

#ifndef _Audio_HPP_
#define _Audio_HPP_

#include <iostream>

class Audio
{
    public:
        Audio();
        ~Audio();

        void pause(float second) const;
};

#endif