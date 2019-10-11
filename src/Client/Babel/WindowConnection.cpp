/*
** EPITECH PROJECT, 2018
** CPP_babel_2019
** File description:
** src/Client/Babel/WindowConnection.cpp
*/

#include <stdlib.h>
#include <time.h>
#include "WindowConnection.hpp"
#include "WindowProgram.hpp"

WindowConnection::WindowConnection(QWidget *parent) : AbstractWindow(parent)
{
    _parent->setFixedSize(800, 600);

    setWallpaper();

    _effect = new QGraphicsDropShadowEffect(this);
    _effect->setBlurRadius(3);
    _effect->setColor(QColor("black"));
    _effect->setOffset(1,1);

    _textConnect = createLabel("Choose your nickname", 400, 70, 200, 100,
    "font: 42pt; color : white;", Qt::AlignHCenter);
    _textConnect->setGraphicsEffect(_effect);
    _elements.push_back(_textConnect);

    _textInput = createLineEdit("", 500, 50, 150, 275, "font: 28pt;");
    _textInput->setFocus();
    _elements.push_back(_textInput);

    _textButtonIcon = new QIcon("ressources/boneIcon.png");
    _woofButton = createButtonIcon(*_textButtonIcon, "WOOF", 200, 60, 300, 400, 50, 50, "font: 28pt;");
    _woofButton->setEnabled(false);
    _elements.push_back(_woofButton);

    _full = createButtonIcon(*_textButtonIcon, "WOOF", 1, 1, 800, 600, 1, 1, "");
    _elements.push_back(_full);

    initSound();
    connectElements();
    showWindow();
}

WindowConnection::~WindowConnection()
{
    destroyElements();
    delete _processLabel;
    delete _animatedWallpaper;
}

void WindowConnection::setWallpaper()
{
    std::vector<std::string> wallpapers = {};

    for (int i = 1; i != 19; i += 1)
        wallpapers.push_back("ressources/wallpapers/d" + std::to_string(i) + ".gif");

    srand(time(NULL));

    _animatedWallpaper = new QMovie(wallpapers[rand() % wallpapers.size()].c_str());
    _animatedWallpaper->setScaledSize(QSize(800, 600));
    _processLabel = new QLabel(this);
    _processLabel->setMovie(_animatedWallpaper);
    _animatedWallpaper->start();
}

void WindowConnection::initSound()
{
    _sounds["Woof"] = new QSoundEffect();
    _sounds["Woof"]->setSource(QUrl::fromLocalFile("ressources/sounds/gooddog.wav"));

    _sounds["WafWaf"] = new QSoundEffect();
    _sounds["WafWaf"]->setSource(QUrl::fromLocalFile("ressources/sounds/wafwaf.wav"));
}

void WindowConnection::connectElements()
{
    connect(_woofButton, SIGNAL(clicked()), this, SLOT(woofButtonTrigger()));
    connect(_textInput, SIGNAL(textChanged(const QString&)), this, SLOT(pseudoTextTrigger(const QString&)));
    connect(_textInput, SIGNAL(returnPressed()), this, SLOT(woofButtonTrigger()));
}

void WindowConnection::woofButtonTrigger()
{
    WindowProgram *tmpParent = static_cast<WindowProgram *>(_parent);

    if (_textInput->text().size() < 3 || _textInput->text().size() > 20)
        return;
    _sounds["Woof"]->play();
    bool connexion = tmpParent->getClient()->run("192.168.43.159", "7171");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (connexion == false)
        return;
    tmpParent->setUsername(_textInput->text());
    tmpParent->getClient()->setUsername(_textInput->text().toStdString());
    tmpParent->setWindow(APP);
}

void WindowConnection::pseudoTextTrigger(const QString &text)
{
    std::string name = text.toStdString();

    if (name[name.length() - 1] == ' ') {
        name = name.substr(0, name.size() - 1);
        _textInput->setText(QString::fromUtf8(name.c_str()));
        return;
    }

    _sounds["WafWaf"]->play();
    _woofButton->setEnabled(name.length() < 3 || name.length() > 20 ? false : true);
}