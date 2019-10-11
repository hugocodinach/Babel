/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** include/Client/Qt/IWindow.hpp
*/

#ifndef _IWINDOW_HPP_
#define _IWINDOW_HPP_

#include <Qt>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QString>
#include <QWidget>
#include <QBoxLayout>
#include <QSoundEffect>
#include <QPixmap>
#include <QGridLayout>
#include <QMovie>
#include <QApplication>
#include <QDesktopWidget>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
#include <iostream>
#include <QFrame>
#include "TextField.hpp"

class IWindow
{
    public:
        virtual ~IWindow() = default;

        virtual QPushButton *createButtonIcon(QIcon icon, QString buttonText, int width, int height,
        int posX, int posY, int iconWidth, int iconHeight, QString styleSheet) = 0;

        virtual QPushButton *createButton(QString buttonText, int width, int height,
        int posX, int posY, QString styleSheet) = 0;

        virtual TextField *createTextEdit(QString textEditText, int width, int height, int posX,
        int posY, QString styleSheet, Qt::ScrollBarPolicy verticalScrollBar, Qt::ScrollBarPolicy horizontalScrollBar) = 0;

        virtual QLineEdit *createLineEdit(QString textEditText, int width, int height, int posX,
        int posY, QString styleSheet) = 0;

        virtual QLabel *createLabel(QString text, int width, int height, int posX, int posY, QString styleSheet,
        Qt::Alignment align) = 0;

        virtual QFrame *createSeparator(QFrame::Shape shape, int width, int height, int posX, int posY) = 0;

        virtual void showWindow() = 0;
        virtual void destroyElements() = 0;
        virtual void destroySounds() = 0;
        virtual void initSound() = 0;
};

#endif