/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/NetworkCommunication/NetworkClient.hpp
*/

#ifndef NETWORK_CLIENT
    #define NETWORK_CLIENT

    #include <iostream>
    #include <string>
    #include <boost/asio.hpp>
    #include <boost/algorithm/string.hpp>
    #include <QWidget>

    class NetworkClient : public QWidget
    {
        Q_OBJECT

        public:
            NetworkClient();
            ~NetworkClient();

            void listen(void);
            bool run(std::string ip, std::string port);
            void createRoom();
            void joinRoom(int id);
            void room();
            void infoRoom(int id);
            void leaveRoom();
            void setUsername(std::string name);
            void quit();
            void chat(std::string msg);
            void ready();
            void getIp();
            void getMyIp();
            void declineCall(std::string name);
            void endCall(std::string name);
            void acceptCall(std::string name);

            void pointerFct(std::vector<std::string> arr);
            void setIp(std::vector<std::string> arr);
            void setMyIp(std::vector<std::string> arr);
            void setNewIp(std::vector<std::string> arr);
            void usersConnected(std::vector<std::string> arr);
            void getChat(std::vector<std::string> arr);
			void whatRoom(std::vector<std::string> arr);
			void whoCallMe(std::vector<std::string> arr);
			void getDeclined(std::vector<std::string> arr);
			void callGetEnd(std::vector<std::string> arr);
            void callAccepted(std::vector<std::string> arr);
            void unstask();

			void askToTalk(std::string name);
			void startCall(std::string peopletotalk);

            std::vector<std::string> _action;
            std::vector<std::string> _ipother;
            std::string _myip = "";
            QObject *_udp = nullptr;
            bool _waitResponse = false;

        signals:
            void listUsersConnected(std::vector<std::string>);
            void chatReceiveMessage(std::string);
            void someoneCallMe(std::string);
            void callGetDeclined();
            void endCallBeforeAccept();
            void endCallAfterAccept();
            void callIsAccepted();

        private:
            std::string _ip;
            std::string _port;
            boost::asio::ip::tcp::tcp::iostream *_tcpStream;
            std::thread _thread;
            std::thread _threadd;
            std::string _name;
            bool _is_running;
			int _room = -1;
			bool contactisok = false;
            typedef struct command_s {
                const char *cmd;
                void (NetworkClient::*cmd_name)(std::vector<std::string> arr);
            } command_t;
    };

#endif