/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** src/Client/Babel/WindowConnection.cpp
*/

#include "CallButton.hpp"
#include "WindowDaugio.hpp"

CallButton::CallButton(QIcon icon, QString buttonText, QWidget *parent) : QPushButton(icon, buttonText, parent), _parent(parent), _name(buttonText)
{
    connect(this, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

CallButton::~CallButton()
{
}

void CallButton::buttonClicked()
{
    (static_cast<WindowDaugio *>(_parent))->setCallingStatus(true);
    (static_cast<WindowDaugio *>(_parent))->disableCalls();
    (static_cast<WindowDaugio *>(_parent))->call(_name);
}