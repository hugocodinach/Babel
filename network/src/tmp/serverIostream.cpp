
#include <iostream>
#include <string>
#include <boost/asio.hpp>

int main()
{
	boost::asio::io_service io_service;

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 7171);
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);

        boost::asio::io_service io_service;
		
		// Création d'un serveur
		

	while (1)
	{
		boost::asio::ip::tcp::iostream stream;
		acceptor.accept(*stream.rdbuf());
		stream << "Bienvenue sur le serveur ! "<< std::endl;
	}
        io_service.run();


	return 0;
}