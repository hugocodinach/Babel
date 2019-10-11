/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** include/Client/Qt/AbstractWindow.hpp
*/

#ifndef _ABSTRACTWINDOW_HPP_
#define _ABSTRACTWINDOW_HPP_

#include <vector>
#include <map>
#include <QMainWindow>
#include "IWindow.hpp"

enum WindowType {
    CONNECT,
    APP
};

class AbstractWindow : public QWidget, public IWindow
{
    public:
        AbstractWindow(QWidget *parent = nullptr);
        ~AbstractWindow();

        QPushButton *createButtonIcon(QIcon icon, QString buttonText, int width, int height,
        int posX, int posY, int iconWidth, int iconHeight, QString styleSheet) final;

        QPushButton *createButton(QString buttonText, int width, int height,
        int posX, int posY, QString styleSheet) final;

        TextField *createTextEdit(QString textEditText, int width, int height, int posX,
        int posY, QString styleSheet, Qt::ScrollBarPolicy verticalScrollBar, Qt::ScrollBarPolicy horizontalScrollBar) final;

        QLineEdit *createLineEdit(QString textLineText, int width, int height, int posX,
        int posY, QString styleSheet) final;

        QFrame *createSeparator(QFrame::Shape shape, int width, int height, int posX, int posY) final;

        QLabel *createLabel(QString text, int width, int height, int posX, int posY, QString styleSheet,
        Qt::Alignment align) final;

        void showWindow() final;
        void destroyElements() final;
        void destroySounds() final;
        virtual void connectElements() = 0;
        virtual void initSound() = 0;



    protected:
        std::map<std::string, QSoundEffect *> _sounds;
        std::vector<QWidget *> _elements;
        QWidget *_parent;

};

#endif