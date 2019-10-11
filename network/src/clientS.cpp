#include <client.hpp>

Client::Client(int fd, std::string clientName, Room *room, char *ip, int port)
{
    _fd = fd;
    _username = clientName;
    _whichRoom = -1;
    _room = room;
    _ready = false;
    _chief = false;
    _character = 0;
    _idingame = -1;
    _ip = std::string(ip);
    _port = port;
}

Client::~Client()
{
}

int Client::getFd(void)
{
    return _fd;
}

int Client::getWhichRoom(void)
{
    return _whichRoom;
}

Room *Client::getRoom(void)
{
    if (_room == NULL) {
        // std::cout << "WTFFFFF?" << std::endl;
    }
    return _room;
}

void Client::setWhichRoom(Room* room)
{
    _room = room;
    _whichRoom = room->getRoomId();
}

// void Client::setCharacter(int character)
// {
// 	_character = character;
// }

int Client::getCharacter()
{
    return _character;
}

void Client::setUsername(std::string name)
{
    _username = name;
}

std::string Client::getUsername(void)
{
    return _username;
}

// void Client::setStatus(bool status)
// {
//     _ready = status;
// }

// bool Client::getStatus(void)
// {
//     return _ready;
// }

// void Client::setChief(bool status)
// {
//     _chief = status;
// }

// bool Client::getChief(void)
// {
//     return _chief;
// }

// void Client::setPosition(int x, int y)
// {
// 	_x = x;
// 	_y = y;
// }

// std::string Client::getPosition()
// {
// 	std::string str = std::to_string(_x) + " " + std::to_string(_y);
// 	return str;
// }

int Client::getPort(void)
{
    return _port;
}

std::string Client::getIp(void)
{
    return _ip;
}

int Client::getId(void)
{
    return _id;
}