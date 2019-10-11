/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** include/Client/Babel/WindowProgram.hpp
*/

#ifndef _WINPROGRAM_HPP_
#define _WINPROGRAM_HPP_

#include "AbstractWindow.hpp"
#include "WindowConnection.hpp"
#include "WindowDaugio.hpp"
#include "NetworkClient.hpp"

class WindowProgram : public AbstractWindow
{
    public:
        WindowProgram(QWidget *parent = nullptr);
        ~WindowProgram();

        void initSound() final;
        void connectElements() final;
        void setWindow(WindowType winType);

        void setUsername(QString username);
        QString getUsername();
        NetworkClient *getClient();

        void closeEvent(QCloseEvent *event) override;

    private:
        IWindow *_win;
        NetworkClient *_client;
        QString _username;
        WindowType _type;
};

#endif