/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** src/Client/Babel/WindowDaugio.cpp
*/

#include <stdlib.h>
#include <time.h>
#include <thread>
#include <QDialog>
#include <boost/algorithm/string.hpp>
#include "WindowDaugio.hpp"
#include "WindowProgram.hpp"
#include "myudp.hpp"

WindowDaugio::WindowDaugio(QWidget *parent) : AbstractWindow(parent), _isCalling(false)
{
    _parent->setFixedSize(1600, 900);

    QLabel *_label_logo = new QLabel(this);
    QPixmap *_pixmap_logo = new QPixmap("ressources/daugioLogo.png");
    _label_logo->setPixmap((*_pixmap_logo).scaled(150, 100));
    _label_logo->move(1275, 0);


    _muteVoiceIcon = new QIcon("ressources/muteVoice.png");
    _muteVoiceButton = createButtonIcon(*_muteVoiceIcon, " Mute Voice", 150, 60, 50, 800, 25, 25, "font: 15pt;");
    _elements.push_back(_muteVoiceButton);

    _muteSoundIcon = new QIcon("ressources/muteSound.png");
    _muteSoundButton = createButtonIcon(*_muteSoundIcon, " Mute Sound", 150, 60, 250, 800, 25, 25, "font: 15pt;");
    _elements.push_back(_muteSoundButton);

    _muteVoiceButton->setEnabled(false);
    _muteSoundButton->setEnabled(false);

    _disconnectIcon = new QIcon("ressources/disconnect.png");
    _disconnectButton = createButtonIcon(*_disconnectIcon, " Disconnect", 150, 60, 450, 800, 25, 25, "font: 15pt;");
    _elements.push_back(_disconnectButton);

    _quitIcon = new QIcon("ressources/exit.png");
    _quitButton = createButtonIcon(*_quitIcon, " Exit Daugio", 150, 60, 650, 800, 25, 25, "font: 15pt;");
    _elements.push_back(_quitButton);

    _traductionIcon = new QIcon("ressources/becomeABonToutou.png");
    _traductionButton = createButtonIcon(*_traductionIcon, " Become a bon toutou", 200, 60, 850, 800, 25, 25, "font: 15pt;");
    _elements.push_back(_traductionButton);

    _hLine = createSeparator(QFrame::HLine, 1105, 10, 0, 780);
    _vLine = createSeparator(QFrame::VLine, 10, 900, 1100, 0);
    _chatChannelLine = createSeparator(QFrame::VLine, 10, 780, 550, 0);
    _elements.push_back(_hLine);
    _elements.push_back(_vLine);
    _elements.push_back(_chatChannelLine);

    _contactArea = new QScrollArea(this);
    _contactArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    _contactArea->setWidgetResizable( true );
    _contactArea->setGeometry( 1150, 430, 400, 400 );

    _contactAreaContent = new QWidget();
    _contactArea->setWidget( _contactAreaContent );

    _contactAreaLayout = new QVBoxLayout();
    _contactAreaLayout->setAlignment(Qt::AlignTop);
    _contactAreaContent->setLayout( _contactAreaLayout );

    _callIcon = new QIcon("ressources/callIcon.png");

    _chatListView = new QListView(this);
    _chatListView->move(570, 20);
    _chatListView->setFixedSize(520, 700);
    _chatListView->setStyleSheet("font: 18pt;");
    _chatListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _elements.push_back(_chatListView);

    _chatInput = createLineEdit("", 400, 30, 570, 730, "");
    _chatInput->setFocus();
    _elements.push_back(_chatInput);

    _chatButton = createButton("Bark", 115, 30, 975, 730, "");
    _chatButton->setEnabled(false);
    _elements.push_back(_chatButton);

    _chatListModel = new QStringListModel(this);

    _chatListView->setModel(_chatListModel);

    setGif();

    initSound();
    connectElements();
    showWindow();
}

WindowDaugio::~WindowDaugio()
{
    destroyElements();
}

void WindowDaugio::initSound()
{
    _sounds["Exit"] = new QSoundEffect();
    _sounds["Exit"]->setSource(QUrl::fromLocalFile("ressources/sounds/ptitchien.wav"));

    _sounds["Disconect"] = new QSoundEffect();
    _sounds["Disconect"]->setSource(QUrl::fromLocalFile("ressources/sounds/reviens.wav"));

    _sounds["WaitingSound"] = new QSoundEffect();
    _sounds["WaitingSound"]->setSource(QUrl::fromLocalFile("ressources/sounds/waitingSound.wav"));
    _sounds["WaitingSound"]->setLoopCount(QSoundEffect::Infinite);
}

void WindowDaugio::connectElements()
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);

    connect(_quitButton, SIGNAL(clicked()), this, SLOT(exitButtonTrigger()));
    connect(_disconnectButton, SIGNAL(clicked()), this, SLOT(disconnectButtonTrigger()));
    connect(_muteVoiceButton, SIGNAL(clicked()), this, SLOT(muteButtonTrigger()));
    connect(_muteSoundButton, SIGNAL(clicked()), this, SLOT(soundButtonTrigger()));
    connect(_chatButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(_chatInput, SIGNAL(textChanged(const QString&)), this, SLOT(chatInputChanged(const QString&)));
    connect(_chatInput, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
    connect(tmpParent->getClient(), SIGNAL(listUsersConnected(std::vector<std::string>)),
    this, SLOT(usersConnected(std::vector<std::string>)));
    connect(tmpParent->getClient(), SIGNAL(chatReceiveMessage(std::string)),
    this, SLOT(receiveMessage(std::string)));
    connect(tmpParent->getClient(), SIGNAL(someoneCallMe(std::string)),
    this, SLOT(getCalled(std::string)));
    connect(tmpParent->getClient(), SIGNAL(callGetDeclined()), this, SLOT(deleteCallElement()));
    connect(tmpParent->getClient(), SIGNAL(endCallBeforeAccept()), this, SLOT(deleteWaitElement()));
    connect(tmpParent->getClient(), SIGNAL(endCallAfterAccept()), this, SLOT(deleteCallElement()));
    connect(tmpParent->getClient(), SIGNAL(callIsAccepted()), this, SLOT(callAccepted()));
}

void WindowDaugio::callAccepted()
{
    if (_sounds["WaitingSound"]->isPlaying() == true)
        _sounds["WaitingSound"]->stop();
    _muteVoiceButton->setEnabled(true);
    _muteSoundButton->setEnabled(true);
}

void WindowDaugio::setGif()
{
    std::vector<std::string> wallpapers;

    for (int i = 1; i != 19; i += 1)
        wallpapers.push_back("ressources/wallpapers/d" + std::to_string(i) + ".gif");

    srand(time(NULL));

    _gif = new QMovie(wallpapers[rand() % wallpapers.size()].c_str());
    QSize wallpaperSize(400, 300);
    _gif->setScaledSize(wallpaperSize);
    QLabel *processLabel = new QLabel(this);
    processLabel->move(1150, 110);
    processLabel->setFixedSize(400, 300);
    processLabel->setMovie(_gif);
    _gif->start();
}

void WindowDaugio::getCalled(std::string caller)
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);

    _disconnectButton->setEnabled(false);
    _quitButton->setEnabled(false);
    _sounds["WaitingSound"]->play();
    disableCalls();
    setCallingStatus(true);

    _calledBG = new QLabel(this);
    _calledBG->move(20, 20);
    _calledBG->setFixedSize(510, 740);
    _calledBG->setStyleSheet("QLabel { background-color : black }");
    _calledBG->show();

    _animatedPhone = new QMovie("ressources/wallpapers/d15.gif");
    _animatedPhone->setScaledSize(QSize(313, 333));
    _animatedPhoneLabel = new QLabel(this);
    _animatedPhoneLabel->setMovie(_animatedPhone);
    _animatedPhoneLabel->move(20 + (255 - (313 / 2)), 130);
    _animatedPhone->start();
    _animatedPhoneLabel->show();

    _caller = new QString(QString::fromStdString(caller));

    _callingName = new QLabel(QString::fromStdString(caller) + " is calling you", this);
    _callingName->move(20 + (255 - (_callingName->minimumSizeHint().width())), 130 + 333 + 20);
    _callingName->setStyleSheet("font: 20pt; color: white");
    _callingName->show();

    _pickUpCalledIcon = new QIcon("ressources/pickUp.png");
    _pickUpCalledButton = createButtonIcon(*_pickUpCalledIcon, "  Pick Up", 150, 60, 255 + 65, 160 + 333 + 60, 25, 25, "font: 20pt; color: green");
    _pickUpCalledButton->show();

    _hangUpCalledIcon = new QIcon("ressources/hangUp.png");
    _hangUpCalledButton = createButtonIcon(*_hangUpCalledIcon, "  Hang Up", 150, 60, 255 - 175, 160 + 333 + 60, 25, 25, "font: 20pt; color: red");
    _hangUpCalledButton->show();

    connect(_hangUpCalledButton, SIGNAL(clicked()), this, SLOT(getCalledCloseH()));
    connect(_pickUpCalledButton, SIGNAL(clicked()), this, SLOT(getCalledCloseP()));
}

void WindowDaugio::getCalledCloseH()
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);

    tmpParent->getClient()->declineCall(_caller->toStdString());
    deleteWaitElement();
}

void WindowDaugio::deleteWaitElement()
{
    _sounds["WaitingSound"]->stop();
    enableCalls();
    setCallingStatus(false);
    delete(_calledBG);
    delete(_callingName);
    delete(_animatedPhone);
    delete(_animatedPhoneLabel);
    delete(_pickUpCalledIcon);
    delete(_pickUpCalledButton);
    delete(_hangUpCalledIcon);
    delete(_hangUpCalledButton);
    _disconnectButton->setEnabled(true);
    _quitButton->setEnabled(true);
}

void WindowDaugio::getCalledCloseP()
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);

    delete(_calledBG);
    delete(_callingName);
    delete(_animatedPhone);
    delete(_animatedPhoneLabel);
    delete(_pickUpCalledIcon);
    delete(_pickUpCalledButton);
    delete(_hangUpCalledIcon);
    delete(_hangUpCalledButton);
    tmpParent->getClient()->acceptCall(_caller->toStdString());
    createCallInterface(*_caller);
}

void WindowDaugio::call(QString dogName)
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);

    _sounds["WaitingSound"]->play();
    tmpParent->getClient()->startCall(dogName.toStdString());
    createCallInterface(dogName);
}

void WindowDaugio::createCallInterface(QString dogName)
{
    _disconnectButton->setEnabled(false);
    _quitButton->setEnabled(false);

    _callBG = new QLabel(this);
    _callBG->move(20, 20);
    _callBG->setFixedSize(510, 740);
    _callBG->setStyleSheet("QLabel { background-color : black }");
    _callBG->show();

    std::vector<std::string> pics = {"ressources/callers/bulldog.png",
    "ressources/callers/caniche.png", "ressources/callers/carlin.png",
    "ressources/callers/husky.png", "ressources/callers/labrador.png",
    "ressources/callers/teckel.png", "ressources/callers/yorkshire.png"};

    srand(time(NULL));

    _contactPicLabel  = new QLabel(this);
    _contactPicPixMap = new QPixmap(pics[rand() % pics.size()].c_str());
    QSize imageSize = ((*_contactPicPixMap).scaled(313, 333, Qt::KeepAspectRatio)).size();
    _contactPicLabel->setPixmap((*_contactPicPixMap).scaled(313, 333, Qt::KeepAspectRatio));
    _contactPicLabel->move(20 + (255 - (imageSize.width() / 2)), 130);
    _contactPicLabel->show();

    _caller = new QString(dogName);

    _calledName = new QLabel(dogName, this);
    _calledName->move(20 + (255 - (_calledName->minimumSizeHint().width())), 130 + imageSize.height() + 20);
    _calledName->setStyleSheet("font: 20pt; color: white");
    _calledName->show();

    _hangUpIcon = new QIcon("ressources/hangUp.png");
    _hangUpButton = createButtonIcon(*_hangUpIcon, "  Hang Up", 150, 60, 255 - 65, 160 + imageSize.height() + 60, 25, 25, "font: 20pt;");
    _hangUpButton->show();
    connect(_hangUpButton, SIGNAL(clicked()), this, SLOT(hangUp()));
}

void WindowDaugio::hangUp()
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);

    tmpParent->getClient()->endCall(_caller->toStdString());
}

void WindowDaugio::deleteCallElement()
{
    if (_sounds["WaitingSound"]->isPlaying() == true)
        _sounds["WaitingSound"]->stop();
    enableCalls();
    setCallingStatus(false);
    delete(_caller);
    delete(_callBG);
    delete(_contactPicLabel);
    delete(_contactPicPixMap);
    delete(_calledName);
    delete(_hangUpIcon);
    delete(_hangUpButton);
    _muteVoiceButton->setEnabled(false);
    _muteSoundButton->setEnabled(false);
    _disconnectButton->setEnabled(true);
    _quitButton->setEnabled(true);
}

void WindowDaugio::disableCalls()
{
    for (int i = 0; i != _contactCallList.size(); i += 1)
        _contactCallList[i]->setEnabled(false);
}

void WindowDaugio::enableCalls()
{
    for (int i = 0; i != _contactCallList.size(); i += 1)
        _contactCallList[i]->setEnabled(true);
}

void WindowDaugio::setCallingStatus(bool status)
{
    _isCalling = status;
}

void WindowDaugio::chatInputChanged(const QString& text)
{
    std::string message = text.toStdString();

    _chatButton->setEnabled((message.length() != 0) ? true : false);
}

void WindowDaugio::exitButtonTrigger()
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);

    _sounds["Exit"]->play();
    tmpParent->getClient()->quit();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    _parent->close();
}

void WindowDaugio::disconnectButtonTrigger()
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);

    _sounds["Disconect"]->play();
    tmpParent->getClient()->quit();
    tmpParent->setWindow(CONNECT);
}

void WindowDaugio::muteButtonTrigger()
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);
    MyUDP *udp = static_cast<MyUDP *>(tmpParent->getClient()->_udp);

    if (udp->getBabel()->getStreamIn()->isStreamActive() == true) {
        udp->stopSendVoice();
        udp->stopStreamIn();
    } else {
        udp->startStreamIn();
        udp->startSendVoice(tmpParent->getClient()->_ipother);
    }
}

void WindowDaugio::soundButtonTrigger()
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);
    MyUDP *udp = static_cast<MyUDP *>(tmpParent->getClient()->_udp);

    if (udp->getBabel()->getStreamOut()->isStreamActive() == true) {
        udp->stopStreamOut();
    } else {
        udp->startStreamOut();
    }
}

void WindowDaugio::sendMessage()
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);

    if (_chatInput->text().size() < 1)
        return;
    tmpParent->getClient()->chat(_chatInput->text().toStdString());
    _chatInput->setText("");
}

void WindowDaugio::receiveMessage(std::string msg)
{
    QString message = QString::fromStdString(msg);
    _chatStringList << message;
    _chatListModel->setStringList(_chatStringList);
    _chatListView->scrollToBottom();
}

void WindowDaugio::usersConnected(std::vector<std::string> arr)
{
    for (QPushButton *oldButton : _contactCallList) {
        _contactAreaLayout->removeWidget(oldButton);
        delete oldButton;
    }
    for (QFrame *oldFrame : _contactFrameList) {
        _contactAreaLayout->removeWidget(oldFrame);
        delete oldFrame;
    }

    _contactCallList.clear();
    _contactFrameList.clear();
    _contactNameList.clear();

    for (std::string name : arr)
        _contactNameList.push_back(name);

    std::vector<std::string> tmp;

    for (int i = 0; i < _contactNameList.size(); i++) {
        boost::split(tmp, _contactNameList[i], boost::is_any_of(" "));
        CallButton *callButton = new CallButton(*_callIcon, "  " + QString::fromUtf8(tmp[0].c_str()), this);
        callButton->setStyleSheet("font: 18pt;");
        _contactAreaLayout->addWidget(callButton);
        _contactCallList.push_back(callButton);
        if (std::atoi(tmp[1].c_str()) != -1)
            callButton->setEnabled(false);
        QFrame *separator = new QFrame();
        separator->setFrameShape(QFrame::HLine);
        separator->setFrameShadow(QFrame::Sunken);
        _contactAreaLayout->addWidget(separator);
        _contactFrameList.push_back(separator);
    }
    if (_isCalling == true)
        disableCalls();
}

bool WindowDaugio::getIsCalling() const
{
    return _isCalling;
}

QString *WindowDaugio::getCaller()
{
    return _caller;
}
