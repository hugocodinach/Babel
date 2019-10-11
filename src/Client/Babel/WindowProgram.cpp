/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** src/Client/Babel/ProgramWindow.cpp
*/

#include "WindowProgram.hpp"
#include "myudp.hpp"

WindowProgram::WindowProgram(QWidget *parent) : AbstractWindow(parent)
{
    _win = nullptr;
    _client = new NetworkClient();

    setWindowTitle("Daugio");

    setWindow(CONNECT);
    showWindow();
}

WindowProgram::~WindowProgram()
{
    destroyElements();
}

void WindowProgram::setWindow(WindowType winType)
{
    _type = winType;
    if (_win != nullptr)
        static_cast<AbstractWindow *>(_win)->close();
    if (winType == CONNECT)
        _win = new WindowConnection(this);
    if (winType == APP)
        _win = new WindowDaugio(this);
    adjustSize();
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

void WindowProgram::initSound()
{
}

void WindowProgram::connectElements()
{
}

void WindowProgram::setUsername(QString username)
{
    _username = username;
}

void WindowProgram::closeEvent(QCloseEvent *event)
{
    WindowDaugio *tmp;
    MyUDP *udp = static_cast<MyUDP *>(_client->_udp);

    if (_type == APP) {
        tmp = static_cast<WindowDaugio *>(_win);
        if (tmp->getIsCalling() == true) {
            _client->endCall(tmp->getCaller()->toStdString());
            if (udp->getBabel()->getStreamOut()->isStreamActive() == true) {
                udp->stopStreamOut();
            } else {
                udp->startStreamOut();
            }
            if (udp->getBabel()->getStreamIn()->isStreamActive() == true) {
                udp->stopSendVoice();
                udp->stopStreamIn();
            } else {
                udp->startStreamIn();
                udp->startSendVoice(_client->_ipother);
            }
        }
    }
    QWidget::closeEvent(event);
}

QString WindowProgram::getUsername()
{
    return _username;
}

NetworkClient *WindowProgram::getClient()
{
    return _client;
}