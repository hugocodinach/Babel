/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** include/Client/Babel/WindowConnection.hpp
*/

#ifndef _WINCONNECTION_HPP_
#define _WINCONNECTION_HPP_

#include "AbstractWindow.hpp"

class WindowConnection : public AbstractWindow
{
    Q_OBJECT

    public:
        WindowConnection(QWidget *parent = nullptr);
        ~WindowConnection();

        void initSound() final;
        void setWallpaper();
        void connectElements() final;

    public slots:
        void woofButtonTrigger();
        void pseudoTextTrigger(const QString &text);

    private:
        QPushButton *_woofButton;
        QPushButton *_full;
        QLineEdit *_textInput;
        QLabel *_textConnect;
        QLabel *_processLabel;
        QGraphicsDropShadowEffect *_effect;
        QIcon *_textButtonIcon;
        QMovie *_animatedWallpaper;
};

#endif