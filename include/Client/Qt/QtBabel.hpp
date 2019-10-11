/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** include/Client/Qt/QtBabel.hpp
*/

#ifndef _QTBABEL_HPP_
#define _QTBABEL_HPP_

#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QFontDatabase>

class QtBabel
{
    public:
        QtBabel(int ac, char **av);
        ~QtBabel();

        void exec();

    private:
        QApplication *_app;
};

#endif