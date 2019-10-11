#include <boost/asio.hpp>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(boost::asio::io_service& ios)
	{
		return pointer(new tcp_connection(ios));
	}

	boost::asio::ip::tcp::socket& socket()
	{
		return m_socket;
	}

	void do_read()
	{
		// On lance une écoute
		boost::asio::async_read(m_socket, boost::asio::buffer(m_buffer),
			boost::bind(&tcp_connection::handle_read, shared_from_this(),
			boost::asio::placeholders::error)
			);
		timer.expires_from_now(boost::posix_time::seconds(5));
		timer.async_wait(boost::bind(&tcp_connection::close, shared_from_this() ));
	}


	void start()
	{
		m_message = "Bienvenue sur le serveur!\n";

		boost::asio::async_write(m_socket, boost::asio::buffer(m_message),
			boost::bind(&tcp_connection::handle_write, shared_from_this(), 
			boost::asio::placeholders::error)
			);
	}

private:	
	tcp_connection(boost::asio::io_service& io_service) 
		: m_socket(io_service), 
		timer(io_service, boost::posix_time::seconds(5)) // Commence à compter dès sa création
	{
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			do_read(); // (2)
		}
		else {
			// std::cout << error.message() << std::endl;
		}
	}

	void handle_read(const boost::system::error_code& error) // (6)
	{
		if (!error)
		{
			// On réécoute
			do_read();
		}
		else 
		{
			close();
		}
	}

	void close() // (7)
	{
		m_socket.close();
	}

	boost::asio::deadline_timer timer;
	boost::asio::ip::tcp::socket m_socket;
	std::string m_message;
	boost::array<char, 128> m_buffer;
};

class tcp_server
{
public:
	tcp_server(boost::asio::io_service& io_service, int port) // (1)
		: m_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
	{
		start_accept();
	}
				
private:
	void start_accept()
        {
                tcp_connection::pointer new_connection = tcp_connection::create(m_acceptor.get_io_service());

                m_acceptor.async_accept(new_connection->socket(), 
		boost::bind(&tcp_server::handle_accept, this, 
		new_connection, boost::asio::placeholders::error));
        }
					
	void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error) // (4)
        {
                if (!error)
                {
                        // std::cout << "Reçu un client!" << std::endl;
                        new_connection->start();
                        start_accept(); // (5)
                }
        }
					
	boost::asio::ip::tcp::acceptor m_acceptor;
};


int main()
{
	try
	{
		boost::asio::io_service io_service;
		
		// Création d'un serveur
		tcp_server server(io_service, 7171);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
			
	return 0;
}