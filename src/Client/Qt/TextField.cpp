/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** src/Client/Babel/WindowConnection.cpp
*/

#include "TextField.hpp"

TextField::TextField(const QString &text, QWidget *parent = 0) : QTextEdit(text, parent)
{
}

TextField::~TextField()
{
}

QString TextField::getQString()
{
    return toPlainText();
}

std::string TextField::getString()
{
    return toPlainText().toStdString();
}

std::string TextField::getStripedString()
{
    std::string str = toPlainText().toStdString();
    size_t start = -1;
    size_t end = -1;

    for (size_t i = 0; i != str.length(); i += 1) {
        if (start == -1 && str[i] != ' ' && str[i] != '\t')
            start = i;
        if (end == -1 && start != -1 && (str[i] == ' ' || str[i] == '\t'))
            end = i;
        if (end != -1 && str[i] != ' ' && str[i] != '\t')
            end = -1;
    }
    if (start == -1 && end == -1)
        return "";
    if (start == -1)
        return str;
    if (end == -1)
        end = str.length();
    return str.substr(start, end - start);
}