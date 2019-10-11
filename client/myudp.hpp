#ifndef MYUDP_HPP
#define MYUDP_HPP

#include <vector>
#include "Babel.hpp"

#include <QObject>
#include <thread>
#include <chrono>
#include <mutex>
#include <QUdpSocket>
#include <boost/algorithm/string.hpp>

class MyUDP : public QObject
{
    Q_OBJECT

    public:
        explicit MyUDP(Babel *babel, QObject *parent = 0);
        void run(std::string ip, int port);
        void packetUDP(std::vector<unsigned char> opus, std::string adress, int port, opus_int32 enc);
        void startSendVoice(std::vector<std::string>);
        void sendVoice(Babel *babel, std::vector<std::string>);
        void stopSendVoice();
        void startStreamIn();
        void stopStreamIn();
		void startStreamOut();
		void stopStreamOut();
        Babel *getBabel();
        bool _run = false;

    public slots:
        void readyReadStream();

    private:
        QUdpSocket *socket;
        Babel *_babel;
        std::thread _thread;
        std::mutex _mtx;
};

#endif