/*
** EPITECH PROJECT, 2018
** main.cpp
** File description:
** src/main.cpp
*/

#include "Babel.hpp"
#include <thread>
#include <chrono>


int SAMPLE_RATE = 48000;
int FRAMES_PER_BUFFER = 480;

int main(int ac, char **av)
{
    Babel *babel = new Babel(ac, av, SAMPLE_RATE, FRAMES_PER_BUFFER);
    qRegisterMetaType<std::vector<std::string>>("std::vector<std::string>");
    qRegisterMetaType<std::string>("std::string");

    babel->getQtBabel()->exec();

    delete babel;
    return (0);

}