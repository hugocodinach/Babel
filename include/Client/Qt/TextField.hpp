/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** include/Client/Babel/WindowConnection.hpp
*/

#ifndef _TEXTFIELD_HPP_
#define _TEXTFIELD_HPP_

#include <iostream>
#include <QTextEdit>
#include <QString>
#include <QWidget>

class TextField : public QTextEdit
{
    Q_OBJECT

    public:
        TextField(const QString &text, QWidget *parent);
        ~TextField();

        QString getQString();
        std::string getString();
        std::string getStripedString();
};

#endif