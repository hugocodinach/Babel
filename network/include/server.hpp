#include <string>
#include <vector>
#include <iostream>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <room.hpp>
#include <boost/algorithm/string.hpp>
#include "unistd.h"
#include "tools.hpp"

class Server
{
    public:
        Server(int port);
        ~Server();
        int run();
        Client *getClient(int);
        int accept_client(int, int);
        void addClient(int, std::string, char *ip, int port);
        void read_from_client(int);
        void deleteClient(Client *);
        Room *addRoom(void);
        void addClientInRoom(Client *, Room *);
        void deleteClientInRoom(Client *, Room *);
        void getServerInfo(void);
        void getServerInfoUser(void);
        std::string getServerInfoRoom(void);
        void checkDeleteRoom(void);
        void pointerFct(Client *, char *);
        Room *getRoomById(int);
        // bool getStatusFrom(Client *client);
		void listenfd();

        // void log(Client *, char *, std::vector<std::string> arr);
        void quit(Client *, char *, std::vector<std::string> arr);
        void chat(Client *, char *, std::vector<std::string> arr);
        void room(Client *, char *, std::vector<std::string> arr);
        void infoRoom(Client *, char *, std::vector<std::string> arr);
        void createRoom(Client *, char *, std::vector<std::string> arr);
        void joinRoom(Client *, char *, std::vector<std::string> arr);
        void leaveRoom(Client *, char *, std::vector<std::string> arr);
        void setUserName(Client *, char *, std::vector<std::string> arr);
        // void play(Client *, char *, std::vector<std::string> arr);
        // void status(Client *, char *, std::vector<std::string> arr);
        // void promote(Client *, char *, std::vector<std::string> arr);
        // void seed(Client *, char *, std::vector<std::string> arr);
		// void setCharacter(Client *, char *, std::vector<std::string> arr);
		// void action(Client *, char *, std::vector<std::string> arr);
		// void dead(Client *, char *, std::vector<std::string> arr);
		// void bonus(Client *, char *, std::vector<std::string> arr);
		// void getCharacter(Client *client, char *buffer, std::vector<std::string> arr);
		void getIp(Client *client, char *buffer, std::vector<std::string> arr);
		void getMyIp(Client *client, char *buffer, std::vector<std::string> arr);
		void askToTalk(Client *client, char *buffer, std::vector<std::string> arr);
		void acceptCall(Client *client, char *buffer, std::vector<std::string> arr);
		void declineCall(Client *client, char *buffer, std::vector<std::string> arr);
		void endCall(Client *client, char *buffer, std::vector<std::string> arr);

		void leaveRoomPers(Client *client, std::string msg);

		void sendMsg(int fdClient, std::string msg);
        bool setSocket(void);
		void showClient(void);

    private:
        std::string _adress;
        int _port;
        std::string path;
        int _status;
        fd_set _read_fd_set;
        fd_set _active_fd_set;
        struct sockaddr_in _addr;
        std::vector<Client *> _clients;
        std::vector<Room *> _rooms;
		Room* _mainRoom;
        int _fdSocket;
        std::thread _thread;
		bool _inthread;
		std::vector<int> _stackfd;

        typedef struct command_s {
            const char *cmd;
            void (Server::*cmd_name)(Client *, char *buffer, std::vector<std::string> arr);
        } command_t;
};