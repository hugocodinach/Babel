#include "myudp.hpp"

MyUDP::MyUDP(Babel *babel, QObject *parent) :
    QObject(parent)
{
    socket = new QUdpSocket(this);
    _babel = babel;
}

void MyUDP::run(std::string ip, int port)
{
    socket->bind(QHostAddress(ip.c_str()), port);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReadStream()));
}

void MyUDP::packetUDP(std::vector<unsigned char> opus, std::string adress, int port, opus_int32 enc)
{
    QByteArray Data;
    for (unsigned int ct = 0; ct != opus.size(); ct ++) {
        Data.append(opus[ct]);
    }

    Data.append(enc);

    socket->writeDatagram(Data, QHostAddress(adress.c_str()), port);
}


void MyUDP::readyReadStream()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    std::vector<unsigned char> voice;
    opus_int32 enc;
    
    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);


    for (unsigned int ct = 0; ct != buffer.size(); ct ++) {
        voice.push_back((buffer[ct]));
    }
    enc = static_cast<int>(voice.back());

    if (_babel->getStreamOut()->isStreamActive() == true) {
        _babel->getCompressor()->getDecoder()->decode(_babel->_framesPerBuffer , enc, voice, _babel->getStreamOut()->getData());
        _babel->getStreamOut()->writeStream();
    }
}

void MyUDP::sendVoice(Babel *babel, std::vector<std::string> ipother)
{
    opus_int32 enc;
    _run = true;

    while (_run) {
        babel->getStreamIn()->readStream();
        enc = babel->getCompressor()->getEncoder()->encode(480, babel->getStreamIn()->getData(), babel->getCompressor()->getData());
        std::vector<unsigned char> tmp = babel->getCompressor()->getData();
        for (auto e : ipother) {
            std::vector<std::string> arr;
            boost::split(arr, e, boost::is_any_of(" \n"));
            if (arr.size() > 1) {
                packetUDP(tmp, arr[1], 7173, enc);
            }
        }
	    std::this_thread::sleep_for (std::chrono::milliseconds(5));

    }
}

void MyUDP::startStreamOut()
{
    _babel->getStreamOut()->startStream();
}

void MyUDP::stopStreamOut()
{
    _babel->getStreamOut()->stopStream();
}

void MyUDP::startStreamIn()
{
    _babel->getStreamIn()->startStream();
}

void MyUDP::stopStreamIn()
{
    _babel->getStreamIn()->stopStream();
}

void MyUDP::startSendVoice(std::vector<std::string> ipother)
{
    _thread = std::thread([ipother, this]() {sendVoice(this->_babel, ipother);});
}

void MyUDP::stopSendVoice()
{
    _run = false;
    _thread.join();
}

Babel *MyUDP::getBabel()
{
    return _babel;
}
