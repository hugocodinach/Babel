/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/NetworkCommunication.cpp
*/

#include "NetworkClient.hpp"
#include "myudp.hpp"

NetworkClient::NetworkClient() : QWidget()
{
    _is_running = false;
    _tcpStream = nullptr;
}

void NetworkClient::listen(void)
{
    std::string str;

    while (std::getline(*_tcpStream, str)) {
        _action.push_back(str);
    }
}

bool NetworkClient::run(std::string ip, std::string port)
{
    _tcpStream = new boost::asio::ip::tcp::tcp::iostream(ip, port);
    std::string str;
    _is_running = true;
    std::getline(*_tcpStream, str);
    if (str == "") {
        return false;
    }
    _ip = ip;
    _port = port;
    _thread = std::thread([this]() {listen();});
    _name = "user";
    room();
    _threadd = std::thread([this]() {unstask();});
    std::this_thread::sleep_for (std::chrono::milliseconds(1000));
    getMyIp();
    while (_myip == "") {
        std::this_thread::sleep_for (std::chrono::milliseconds(1000));
    }
    MyUDP *udp = static_cast<MyUDP *>(_udp);
    udp->run(_myip, 7173);

    return true;
}

void NetworkClient::createRoom()
{
    *_tcpStream << "CREATEROOM" << std::endl;
}

void NetworkClient::joinRoom(int id)
{
    *_tcpStream << "JOINROOM " << id << std::endl;
}

void NetworkClient::room()
{
    *_tcpStream << "ROOM" << std::endl;
}

void NetworkClient::infoRoom(int id)
{
    *_tcpStream << "INFOROOM " << id << std::endl;
}

void NetworkClient::leaveRoom()
{
    *_tcpStream << "LEAVEROOM" << std::endl;
}


void NetworkClient::chat(std::string msg)
{
    *_tcpStream << "CHAT " << msg << std::endl;
}

void NetworkClient::getIp()
{
    *_tcpStream << "GETIP" << std::endl;
}

void NetworkClient::getMyIp()
{
    *_tcpStream << "GETMYIP" << std::endl;
}

void NetworkClient::setUsername(std::string name)
{
    _name = name;
    *_tcpStream << "SETUSERNAME " << name << std::endl;
}

void NetworkClient::askToTalk(std::string name)
{
    *_tcpStream << "ASKTOTALK " << name << " " << _room << std::endl;
}

void NetworkClient::declineCall(std::string name)
{
    *_tcpStream << "DECLINE_CALL " << name << std::endl;
}

void NetworkClient::endCall(std::string name)
{
    *_tcpStream << "END_CALL " << name << std::endl;
}

void NetworkClient::acceptCall(std::string name)
{
    *_tcpStream << "ACCEPT_CALL " << name << std::endl;
}

void NetworkClient::quit()
{
    if (_tcpStream != nullptr)
        *_tcpStream << "QUIT" << std::endl;
    _is_running = false;
    _thread.join();
    _threadd.join();
}


void NetworkClient::setIp(std::vector<std::string> arr)
{
    arr.pop_back();
    arr.erase(arr.begin());
    _ipother = arr;
}

void NetworkClient::setMyIp(std::vector<std::string> arr)
{
    _myip = arr[1];
}


void NetworkClient::startCall(std::string peopletotalk)
{
    createRoom();
    getMyIp();
    while (_room == -1) {
        std::this_thread::sleep_for (std::chrono::milliseconds(200));
    }
    askToTalk(peopletotalk);
    _waitResponse = true;
}

void NetworkClient::setNewIp(std::vector<std::string> arr)
{
    if (arr.size() == 1)
        return;
    arr.erase(arr.begin());
    _ipother = arr;
}

void NetworkClient::usersConnected(std::vector<std::string> arr)
{
    arr.erase(arr.begin());
    emit listUsersConnected(arr);
}

void NetworkClient::getChat(std::vector<std::string> arr)
{
    emit chatReceiveMessage(arr[1]);
}

void NetworkClient::whatRoom(std::vector<std::string> arr)
{
    _room = std::atoi(arr[1].c_str());
}

void NetworkClient::whoCallMe(std::vector<std::string> arr)
{
    std::vector<std::string> new_arr;

    boost::split(new_arr, arr[1], boost::is_any_of(" "));
    emit someoneCallMe(new_arr[0]);
}

void NetworkClient::getDeclined(std::vector<std::string> arr)
{
    _room = -1;
    _waitResponse = false;
    emit callGetDeclined();
}

void NetworkClient::callAccepted(std::vector<std::string> arr)
{
    MyUDP *udp = static_cast<MyUDP *>(_udp);

    _waitResponse = false;
    _room = std::atoi(arr[1].c_str());
    _myip = arr[2];
    udp->startStreamIn();
    udp->startStreamOut();
    udp->startSendVoice(_ipother);
    emit callIsAccepted();
}

void NetworkClient::callGetEnd(std::vector<std::string> arr)
{
    MyUDP *udp = static_cast<MyUDP *>(_udp);

    if (_room == -1) {
        emit endCallBeforeAccept();
    } else {
        emit endCallAfterAccept();
        if (_waitResponse != true) {
            udp->stopSendVoice();
            udp->stopStreamIn();
            udp->stopStreamOut();
        }
    }
    _room = -1;
}

void NetworkClient::pointerFct(std::vector<std::string> arr)
{
    command_t const arr_cmd[] = {
        {"IP", &NetworkClient::setIp},
        {"MYIP", &NetworkClient::setMyIp},
        {"INFOROOM", &NetworkClient::setNewIp},
        {"USERS_CONNECTED", &NetworkClient::usersConnected},
        {"CHAT", &NetworkClient::getChat},
        {"CREATEROOM", &NetworkClient::whatRoom},
        {"WHO_CALL_ME", &NetworkClient::whoCallMe},
        {"DECLINE_CALL", &NetworkClient::getDeclined},
        {"END_CALL", &NetworkClient::callGetEnd},
        {"CALL_IS_ACCEPTED", &NetworkClient::callAccepted},
    };

    for (auto e : arr_cmd) {
        if (arr[0] == e.cmd) {
            (this->*e.cmd_name)(arr);
            return;
        }
    }
    return;
}

void NetworkClient::unstask()
{
    std::vector<std::string> arr;

    if (_is_running == false)
        return;
    if (_action.size() > 0) {
        for (auto e : _action) {
            std::string str(e);
            boost::split(arr, str, boost::is_any_of("//"));
            pointerFct(arr);
        }
        _action.clear();
    }
    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    unstask();
}

NetworkClient::~NetworkClient()
{
}