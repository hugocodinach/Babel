/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** src/Client/Qt/AbstractWindow.cpp
*/

#include "AbstractWindow.hpp"

AbstractWindow::AbstractWindow(QWidget *parent) : QWidget(parent)
{
    _parent = parent;
}

AbstractWindow::~AbstractWindow()
{
}

QPushButton *AbstractWindow::createButtonIcon(QIcon icon, QString buttonText, int width, int height,
int posX, int posY, int iconWidth, int iconHeight, QString styleSheet)
{
    QPushButton *result = new QPushButton(icon, buttonText, this);

    result->setStyleSheet(styleSheet);
    result->setFixedSize(width, height);
    result->move(posX, posY);
    result->setIconSize(QSize(iconWidth, iconHeight));

    return result;
}

QPushButton *AbstractWindow::createButton(QString buttonText, int width, int height,
int posX, int posY, QString styleSheet)
{
    QPushButton *result = new QPushButton(buttonText, this);

    result->setStyleSheet(styleSheet);
    result->setFixedSize(width, height);
    result->move(posX, posY);

    return result;
}

TextField *AbstractWindow::createTextEdit(QString textEditText, int width, int height, int posX,
int posY, QString styleSheet, Qt::ScrollBarPolicy verticalScrollBar, Qt::ScrollBarPolicy horizontalScrollBar)
{
    TextField *result = new TextField(textEditText, this);

    result->setStyleSheet(styleSheet);
    result->setFixedSize(width, height);
    result->move(posX, posY);
    result->setHorizontalScrollBarPolicy(horizontalScrollBar);
    result->setVerticalScrollBarPolicy(verticalScrollBar);

    return result;
}

QLineEdit *AbstractWindow::createLineEdit(QString textLineText, int width, int height, int posX,
int posY, QString styleSheet)
{
    QLineEdit *result = new QLineEdit(textLineText, this);

    result->setStyleSheet(styleSheet);
    result->setFixedSize(width, height);
    result->move(posX, posY);

    return result;
}

QLabel *AbstractWindow::createLabel(QString text, int width, int height, int posX, int posY,
QString styleSheet, Qt::Alignment align)
{
    QLabel *result = new QLabel(text, this);

    result->setStyleSheet(styleSheet);
    result->setFixedSize(width, height);
    result->move(posX, posY);
    result->setAlignment(align);
    return result;
}

QFrame *AbstractWindow::createSeparator(QFrame::Shape shape, int width, int height, int posX, int posY)
{
    QFrame *separator = new QFrame(this);

    separator->setFrameShape(shape);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setFixedSize(width, height);
    separator->move(posX, posY);
    return separator;
}

void AbstractWindow::showWindow()
{
    for (QWidget *tmp : _elements)
        tmp->show();
    show();
}

void AbstractWindow::destroyElements()
{
    for (QWidget *tmp : _elements)
        delete tmp;
}

void AbstractWindow::destroySounds()
{
    for (std::pair<std::string, QSoundEffect *> tmp : _sounds)
        delete tmp.second;
}