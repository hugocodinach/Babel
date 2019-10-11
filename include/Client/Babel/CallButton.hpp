/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** include/Client/Babel/WindowConnection.hpp
*/

#ifndef _CALL_BUTTON_HPP_
#define _CALL_BUTTON_HPP_

#include <iostream>
#include <QPushButton>
#include <QIcon>
#include <QString>
#include <QWidget>

class CallButton : public QPushButton
{
    Q_OBJECT

    public:
        CallButton(QIcon icon, QString buttonText, QWidget *parent);
        ~CallButton();

    public slots:
        void buttonClicked();

    private:
        QWidget *_parent;
        QString _name;
};

#endif