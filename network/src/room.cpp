#include <room.hpp>

Room::Room(int id)
{
    _roomId = id;
    _testthread = 0;
    _seed = std::to_string(rand() % 10000);
}

Room::~Room()
{
}

int Room::getRoomId(void)
{
    return _roomId;
}

void Room::setRoomId(int id)
{
    _roomId = id;
}

void Room::clientJoin(Client *client)
{
    _clients.push_back(client);
    sendRoomInfo();
}

void Room::clientLeave(Client *client)
{
    if (_testthread == 1) {
        _thread.join();
        _testthread = 0;
    }
    for (unsigned int ct = 0; ct != _clients.size(); ct ++)
        if (client->getFd() == _clients[ct]->getFd()) {
            _clients.erase(_clients.begin() + ct);
            sendRoomInfo();
            return;
        }
}

void Room::sendRoomInfo()
{
    std::string msg;
    int i = 0;
    std::string tmp;

    for (auto a : _clients) {
        msg = "INFOROOM";
        for (auto e : _clients) {
            if (a->getFd() != e->getFd()) {
                msg += "/";
                msg = msg + e->getUsername() + " "; 
                msg += e->getIp();
            }
        }
        dprintf(a->getFd(), "%s\n", msg.c_str());
        a->_idingame = i;
        i += 1;
    }
}

std::string Room:: getRoomInfo(void)
{
    std::string msg = "INFOROOM ";
    std::string tmp;

    if (_clients.size() == 0)
        msg = msg + "-1";
    for (unsigned int ct = 0; ct != _clients.size(); ct ++) {
        tmp = "ready";
        msg = msg + _clients[ct]->getUsername() + " ready "; 
    }
    return msg;
}

void Room::sendMessageUser(std::string msg, Client *client)
{
    for (auto e : _clients) {
        if (client->getFd() != e->getFd())
            dprintf(e->getFd(), "%s\n", msg.c_str());
    }
}

void Room::sendMessageAll(std::string msg)
{
    for (auto e : _clients) {
        dprintf(e->getFd(), "%s\n", msg.c_str());
    }
}

unsigned int Room::getRoomClientNbr(void)
{
    return _clients.size();
}

std::string Room::getIpClients(Client *client)
{
    std::string dest = "IP/";

    for (auto e : _clients) {
        if (e->getFd() != client->getFd())
            dest += e->getUsername() + " " + e->getIp() + " " + std::to_string(e->getPort()) + "/";
    }
    return dest;
}