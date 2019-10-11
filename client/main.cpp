#include <QCoreApplication>
#include "NetworkClient.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // std::vector<unsigned char> opus = { 201, 187, 200, 188, 205, 186 };
    // client.packetUDP(opus, "10.101.52.141", 7172);

	// NetworkClient *client = new NetworkClient;
	// client->run("10.101.52.141", "7171");
	// client->joinRoom(0);
	// sleep(1);
	// client->getIp();
	
    
    MyUDP client;
    
    // client.HelloUDP();
    
    return a.exec();
}