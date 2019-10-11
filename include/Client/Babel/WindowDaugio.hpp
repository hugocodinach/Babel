/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** include/Client/Babel/WindowDaugio.hpp
*/

#ifndef _WINDAUGIO_HPP_
#define _WINDAUGIO_HPP_

#include <QSplitter>
#include <QVBoxLayout>
#include <QFrame>
#include <QScrollArea>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <QLineEdit>
#include <QCloseEvent>
#include "AbstractWindow.hpp"
#include "CallButton.hpp"

class WindowDaugio : public AbstractWindow
{
    Q_OBJECT

    public:
        WindowDaugio(QWidget *parent = nullptr);
        ~WindowDaugio();

        void initSound() final;
        void connectElements() final;
        void setGif();

        void disableCalls();
        void enableCalls();
        void setCallingStatus(bool status);


        void call(QString dogName);
        void createCallInterface(QString dogName);

        bool getIsCalling() const;
        QString *getCaller();

    public slots:
        void exitButtonTrigger();
        void disconnectButtonTrigger();
        void muteButtonTrigger();
        void soundButtonTrigger();
        void sendMessage();
        void chatInputChanged(const QString& text);
        void usersConnected(std::vector<std::string> arr);
        void receiveMessage(std::string msg);
        void getCalled(std::string caller);
        void hangUp();
        void getCalledCloseH();
        void getCalledCloseP();
        void deleteWaitElement();
        void deleteCallElement();
        void callAccepted();

    private:
        QPushButton *_muteVoiceButton;
        QPushButton *_muteSoundButton;
        QPushButton *_disconnectButton;
        QPushButton *_quitButton;
        QPushButton *_traductionButton;

        QIcon *_muteVoiceIcon;
        QIcon *_muteSoundIcon;
        QIcon *_disconnectIcon;
        QIcon *_quitIcon;
        QIcon *_traductionIcon;

        QFrame *_hLine;
        QFrame *_vLine;
        QFrame *_chatChannelLine;

        QMovie *_gif;

        QLabel *_label_logo;
        QPixmap *_pixmap_logo;

        QScrollArea *_contactArea;
        QWidget *_contactAreaContent;
        QVBoxLayout *_contactAreaLayout;

        std::vector<CallButton *> _contactCallList;
        std::vector<QFrame *> _contactFrameList;
        std::vector<std::string> _contactNameList;
        QIcon *_callIcon;

        QListView *_chatListView;
        QStringListModel *_chatListModel;
        QStringList _chatStringList;
        QLineEdit *_chatInput;
        QPushButton *_chatButton;

        QLabel *_callBG;
        QLabel *_contactPicLabel;
        QPixmap *_contactPicPixMap;
        QLabel *_calledName;
        QPushButton *_hangUpButton;
        QIcon *_hangUpIcon;

        QString *_caller;
        QLabel *_calledBG;
        QLabel *_callingName;
        QPushButton *_hangUpCalledButton;
        QIcon *_hangUpCalledIcon;
        QPushButton *_pickUpCalledButton;
        QIcon *_pickUpCalledIcon;
        QMovie *_animatedPhone;
        QLabel *_animatedPhoneLabel;

        bool _isCalling;
};

#endif