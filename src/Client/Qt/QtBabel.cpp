/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** src/Client/Qt/Qt.cpp
*/

#include "QtBabel.hpp"

QtBabel::QtBabel(int ac, char **av)
{
    _app = new QApplication(ac, av);
    QFontDatabase *fontDB = new QFontDatabase();
    int id = fontDB->addApplicationFont("./ressources/dog.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);
    QApplication::setFont(font);
}

QtBabel::~QtBabel()
{
    delete _app;
}

void QtBabel::exec()
{
    _app->exec();
}
