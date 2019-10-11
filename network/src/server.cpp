#include "server.hpp"

Server::Server(int port)
{
    _port = port;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_family = AF_INET;
    _inthread = false;
}

Server::~Server()
{
}

Client *Server::getClient(int fd)
{
    for (unsigned int ct = 0; ct != _clients.size(); ct++) {
        if (fd == _clients[ct]->getFd()) {
            return _clients[ct];
        }
    }
    return nullptr;
}

int Server::accept_client(int fd_sock, int mode)
{
    int fd_new = 0;
    size_t size = 0;

    if (mode == 0) {
        size = sizeof(_addr);
        fd_new = accept(fd_sock, (struct sockaddr *)&_addr, (socklen_t *)&size);
    }
    if (fd_new < 0) {
        fprintf(stderr, "Accept failed.\n");
        return (-1);
    }
    return (fd_new);
}

void Server::addClient(int fd, std::string clientName, char *ip, int port)
{
    Client * new_client = new Client(fd, clientName, _mainRoom, ip, port);
    _clients.push_back(new_client);
    _mainRoom->clientJoin(new_client);
    _mainRoom->sendMessageAll(getServerInfoRoom());
}

Room *Server::addRoom(void)
{
    int id = 0;
    Room *new_room;

    if (_rooms.size() == 0) {
        new_room = new Room(-1);
        _rooms.push_back(new_room);
        return (new_room);
    }
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++) {
        if (_rooms[ct]->getRoomId() > ct)
            id = _rooms[ct]->getRoomId();
        id += 1;
    }
    new_room = new Room(id);
    _rooms.push_back(new_room);
    return new_room;
}

void Server::addClientInRoom(Client *client, Room *room)
{
    Room *old_room = client->getRoom();
    client->setWhichRoom(room);
    room->clientJoin(client);
    deleteClientInRoom(client, old_room);
}

void Server::deleteClientInRoom(Client *client, Room *room)
{
    room->clientLeave(client);
    room->clientLeave(client);
    checkDeleteRoom();
}

void Server::read_from_client(int fdClient)
{
    FILE *fp = fdopen(fdClient, "r");
    char *str = NULL;
    size_t llen;
    int ct = 0;

    if ((ct = getline(&str, &llen, fp)) == -1) {
        deleteClient(getClient(fdClient));
        checkDeleteRoom();
    } else {
        if (ct > 1)
            pointerFct(getClient(fdClient), str);
    }
}

void Server::deleteClient(Client *client)
{
    deleteClientInRoom(client, client->getRoom());
    FD_CLR(client->getFd(), &_active_fd_set);
    close(client->getFd());
    for (unsigned int ct = 0; ct != _clients.size(); ct++) {
        if (_clients[ct] == client) {
            delete(_clients[ct]);
            _clients.erase(_clients.begin() + ct);
            break;
        }
    }
    _mainRoom->sendMessageAll(getServerInfoRoom());
    showClient();
}

void Server::checkDeleteRoom(void)
{
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++)
        if (_rooms[ct]->getRoomClientNbr() == 0 && _rooms[ct] != _mainRoom) {
            delete(_rooms[ct]);
            _rooms.erase(_rooms.begin() + ct);
            break;
        }
}

void Server::getServerInfo(void)
{
    getServerInfoUser();
    getServerInfoRoom();
}

void Server::getServerInfoUser(void)
{
}

std::string Server::getServerInfoRoom(void)
{
    std::string msg = "ROOM ";
    if (_rooms.size() == 0)
        msg = msg + "-1";
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++) {
        if (ct == 0) {
            msg = msg + std::to_string(_rooms[ct]->getRoomId()) + " " + std::to_string(_clients.size()) + " ";
        } else {
            msg = msg + std::to_string(_rooms[ct]->getRoomId()) + " " + std::to_string(_rooms[ct]->getRoomClientNbr()) + " ";
        }
    }
    return msg;
}

Room *Server::getRoomById(int id)
{
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++) {
        if (_rooms[ct]->getRoomId() == id)
            return _rooms[ct];
    }
    return _mainRoom;
}

void Server::quit(Client *client, char *buffer, std::vector<std::string> arr)
{
    deleteClient(client);
    checkDeleteRoom();
    return;
}

void Server::chat(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::string msg = ":";
    arr.erase(arr.begin());
    for (auto e : arr) {
        msg += " ";
        msg += e;
    }
    for (auto e : _clients) {
        sendMsg(e->getFd(), "CHAT/" + std::string(client->getUsername()) + msg);
    }
    return;
}

void Server::room(Client *client, char *buffer, std::vector<std::string> arr)
{
    sendMsg(client->getFd(), getServerInfoRoom());
    return;
}

void Server::infoRoom(Client *client, char *buffer, std::vector<std::string> arr)
{
    if (arr.size() == 1) {
        sendMsg(client->getFd(), "INFOROOM -1");
        return;
    }
    for (std::string::const_iterator it = arr[1].begin(); it != arr[1].end(); it ++)
        if(std::isdigit(*it) == false) {
            sendMsg(client->getFd(), "INFOROOM -1");
            return;
        }
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++) {
        if (atoi(arr[1].c_str()) == _rooms[ct]->getRoomId()) {
            sendMsg(client->getFd(), _rooms[ct]->getRoomInfo());
            return;
        }
    }
    sendMsg(client->getFd(), "INFOROOM -1");
    return;
}

void Server::createRoom(Client *client, char *buffer, std::vector<std::string> arr)
{
    addClientInRoom(client, addRoom());
    sendMsg(client->getFd(), "CREATEROOM/" + std::to_string(client->getWhichRoom()));
    _mainRoom->sendMessageAll(getServerInfoRoom());
    return;
}

void Server::joinRoom(Client *client, char *buffer, std::vector<std::string> arr)
{
    if (arr.size() == 1) {
        sendMsg(client->getFd(), "JOINROOM -1");
        return;
    }
    for (std::string::const_iterator it = arr[1].begin(); it != arr[1].end(); it ++)
        if(std::isdigit(*it) == false) {
            sendMsg(client->getFd(), "JOINROOM -1 ERROR");
            return;
        }
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++) {
        if (atoi(arr[1].c_str()) == _rooms[ct]->getRoomId()) {
            sendMsg(client->getFd(), "JOINROOM OK");
            addClientInRoom(client, _rooms[ct]);
            _mainRoom->sendMessageAll(getServerInfoRoom());
            return;
        }
    }
    sendMsg(client->getFd(), "JOINROOM -1");
}

void Server::leaveRoom(Client *client, char *buffer, std::vector<std::string> arr)
{
    if (client->getWhichRoom() != -1) {
        sendMsg(client->getFd(), "LEAVEROOM " + std::to_string(client->getWhichRoom()));
        deleteClientInRoom(client, client->getRoom());
        client->setWhichRoom(_mainRoom);
        _mainRoom->clientJoin(client);
        _mainRoom->sendMessageAll(getServerInfoRoom());
        return;
    }
    sendMsg(client->getFd(), "JOINROOM -1");
    _mainRoom->sendMessageAll(getServerInfoRoom());
    return;
}

void Server::setUserName(Client *client, char *buffer, std::vector<std::string> arr)
{
    if (arr.size() >= 2) {
        for (auto e : _clients) {
            if (e->getUsername() == arr[1]) {
                arr[1] += "1";
            }
        }
        client->setUsername(arr[1]);
    }
    else
        sendMsg(client->getFd(), "SETUSERNAME -1");
    showClient();
}

void Server::sendMsg(int fdClient, std::string msg)
{
    dprintf(fdClient, "%s\n", msg.c_str());
}

void Server::getIp(Client *client, char *buffer, std::vector<std::string> arr)
{
    sendMsg(client->getFd(), client->getRoom()->getIpClients(client));
}

void Server::getMyIp(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::string dest = "MYIP/" + client->getIp();
    sendMsg(client->getFd(), dest);
}

void Server::askToTalk(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::string dest = "WHO_CALL_ME/";
    std::string dest_two = "ASK_TO_TALK/";

    for (auto e : _clients) {
        if (e->getUsername() == arr[3]) {
            e->_idingame = -2;
            sendMsg(e->getFd(), dest + client->getUsername() + " " + client->getIp() + " " +e->getIp() + " " + arr[4]);
            sendMsg(client->getFd(), dest_two + " " + e->getIp() + " " + client->getIp());
            break;
        }
    }
}

void Server::acceptCall(Client *client, char *buffer, std::vector<std::string> arr)
{
    for (auto e : _clients)
    {
        if (e->getUsername() == arr[1]) {
             e->_idingame = -1;
            arr[1] = std::to_string(e->getWhichRoom());
            joinRoom(client, buffer, arr);
            sendMsg(e->getFd(), "CALL_IS_ACCEPTED/" + arr[1] + "/" + e->getIp());
            sendMsg(client->getFd(), "CALL_IS_ACCEPTED/" + arr[1] + "/" + client->getIp());
            break;
        }
    }
}

void Server::leaveRoomPers(Client *client,  std::string msg)
{
    if (client->getWhichRoom() != -1) {
        sendMsg(client->getFd(), msg);
        deleteClientInRoom(client, client->getRoom());
        client->setWhichRoom(_mainRoom);
        _mainRoom->clientJoin(client);
        _mainRoom->sendMessageAll(getServerInfoRoom());
        return;
    }
    sendMsg(client->getFd(), msg);
    _mainRoom->sendMessageAll(getServerInfoRoom());
    return;
}

void Server::declineCall(Client *client, char *buffer, std::vector<std::string> arr)
{
    for (auto e : _clients)
    {
        if (e->getUsername() == arr[1]) {
            leaveRoomPers(e, "DECLINE_CALL");
        }
    }
}

void Server::endCall(Client *client, char *buffer, std::vector<std::string> arr)
{
    int i = 1;
    if (arr.size() > 3)
        i = 3;
    for (auto e : _clients)
    {
        if (e->getUsername() == arr[i]) {
            leaveRoomPers(e, "END_CALL");
        }
    }
    if (client->getWhichRoom() != -1)
        leaveRoomPers(client, "END_CALL");
}


void Server::showClient()
{
    std::string dest = "USERS_CONNECTED/";
    for (auto e : _clients) {
        for (auto a : _clients) {
            if (a != e) {
                if (a->_idingame == -2)
                    dest += a->getUsername() + " " + "-2" + "/";
                else
                    dest += a->getUsername() + " " + std::to_string(a->getWhichRoom()) + "/";

            }
        }
        dest.pop_back();
        sendMsg(e->getFd(), dest);
        dest = "USERS_CONNECTED/";
    }
}

void Server::pointerFct(Client *client, char *buffer)
{
    command_t const arr_cmd[] = {
    {"QUIT", &Server::quit},
    {"CHAT", &Server::chat},
    {"ROOM", &Server::room},
    {"INFOROOM", &Server::infoRoom}, 
    {"CREATEROOM", &Server::createRoom},
    {"JOINROOM", &Server::joinRoom}, 
    {"LEAVEROOM", &Server::leaveRoom},
    {"SETUSERNAME", &Server::setUserName},
    {"GETIP", &Server::getIp},
    {"GETMYIP", &Server::getMyIp},
    {"ASKTOTALK", &Server::askToTalk},
    {"ACCEPT_CALL", &Server::acceptCall},
    {"DECLINE_CALL", &Server::declineCall},
    {"END_CALL", &Server::endCall}
    };
    std::vector<std::string> arr;
    std::string str(buffer);
    boost::split(arr, str, boost::is_any_of(" \n"));

    for (auto e : arr_cmd) {
        if (arr[0] == e.cmd) {
            (this->*e.cmd_name)(client, buffer, arr);
            showClient();
            return;
        }
    }
    return;
}

bool Server::setSocket(void)
{
    _fdSocket = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;

    if (_fdSocket == -1) {
        fprintf(stderr, "Error opening socket.\n");
        return false;
    }
    if (bind(_fdSocket, (struct sockaddr *)&_addr, sizeof(struct sockaddr_in)) == -1) {
        fprintf(stderr, "Error binding socket.\n");
        return false;
    }
    setsockopt(_fdSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (listen(_fdSocket, 1) < 0) {
        fprintf(stderr, "Listen faild.\n");
        return false;
    }
    return true;
}

int Server::run(void)
{
    int fd = 0;
    int newFd = 0;

    if (setSocket() == false)
        return 84;
    _mainRoom = addRoom();
    FD_ZERO(&_active_fd_set);
    FD_SET(_fdSocket, &_active_fd_set);
    while (1) {
        _read_fd_set = _active_fd_set;
        if (select (FD_SETSIZE, &_read_fd_set, NULL, NULL, NULL) < 0) {
            fprintf(stderr, "Select faild\n");
            _thread.join();
            return 84;
        }
        for (fd = FD_SETSIZE; fd > 0; -- fd) {
            if (FD_ISSET(fd, &_read_fd_set)) {
                if (fd == _fdSocket) {
                    if ((newFd = accept_client(_fdSocket, 0)) == -1) {
                        _thread.join();
                        return 84;
                    }
                    printf("IP address is: %s\n", inet_ntoa(_addr.sin_addr));
                    printf("port is: %d\n", (int) ntohs(_addr.sin_port));
                    FD_SET(newFd, &_active_fd_set);
                    dprintf(newFd, "CONNECTED\n");
                    addClient(newFd, "User", inet_ntoa(_addr.sin_addr), static_cast<int>(ntohs(_addr.sin_port)));
                } else {
                     read_from_client(fd);
                }
            }
        }
    }
    _thread.join();
}

void Server::listenfd()
{
    while (1) {
        if (_stackfd.size() > 0) {
            for (auto e : _stackfd) {
                read_from_client(e);
            }
            _stackfd.clear();
        }
    }
}

int main(int ac, char **arg)
{
    int port = 7171;
    if (ac >= 2)
        port = atoi(arg[1]);
    srand(time(NULL));
    Server Server(port);

    Server.run();
}