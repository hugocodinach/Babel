#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <string>

#include "room.hpp"

class Room;

class Client
{
    public:
        Client(int, std::string, Room *, char *ip, int port);
        ~Client();
        int getFd(void);
        std::string getUsername(void);
        int getWhichRoom(void);
        void setWhichRoom(Room *);
		void setCharacter(int character);
		int getCharacter();
		Room* getRoom();
        void setUsername(std::string);
		std::string getIp(void);
		int getPort(void);
		int getId(void);

		int _idingame;
    private:
        std::string _username;
        int _fd;
        int _whichRoom;
		Room * _room;
        bool _ready;
        bool _chief;
		int _character;
		int _x;
		int _y;
		int _port;
		std::string _ip;
		int _id;
};


#endif