#define _WIN32_WINNT 0x0501
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

        void read() {
            boost::asio::async_read(m_socket, boost::asio::buffer(m_network_buffer),
                boost::asio::transfer_at_least(20),
                boost::bind(&tcp_connection::handle_read, shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        }

        void send(std::string const& message) {
            boost::asio::async_write(m_socket, boost::asio::buffer(message),
			boost::bind(&tcp_connection::handle_write, shared_from_this(), 
			boost::asio::placeholders::error)
			);
            // m_socket.send(boost::asio::buffer(message));
    }

    private:	
        tcp_connection(boost::asio::io_service& io_service) 
            : m_socket(io_service)
        {
        }

        void handle_read(const boost::system::error_code& error, size_t number_bytes_read) // (3)
        {
            if (!error)
            {
                // std::cout.write(&m_network_buffer[0], number_bytes_read);
                read();
            }
            else {
                // std::cout << error.message();
            }
        }

        // void handle_write(const boost::system::error_code& err,size_t bytes_transferred){  
        //     if (!err) {  
        //         srd::cout << "Server sent Hello message!"<< srd::endl;  
        //     } else {  
        //         std::cerr << "error: " << err.message() << srd::endl;  
        //         m_socket.close();  
        //     }  
    //  }  

        void handle_write(const boost::system::error_code& error)
        {
            if (!error)
            {
                // std::cout << "handle read haha" << std::endl;
            }
            else {
                // std::cout << error.message() << std::endl;
            }
        }

        boost::asio::ip::tcp::socket				m_socket;
        boost::array<char, 128> m_network_buffer;
};

class tcp_client
{
    public:
        tcp_client(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint) 
            :m_io_service (io_service)
        {
            // On tente de se connecter au serveur // (1)
            connect(endpoint);
        }

        void send(std::string const& message) {
            new_connection->send(message);
        }

    private:

        void connect(boost::asio::ip::tcp::endpoint& endpoint)
        {
            new_connection = tcp_connection::create(m_io_service);
            boost::asio::ip::tcp::socket& socket = new_connection->socket();
            socket.async_connect(endpoint, boost::bind(&tcp_client::handle_connect, this, new_connection, boost::asio::placeholders::error));
        }

        void handle_connect(tcp_connection::pointer new_connection, const boost::system::error_code& error)
        {
            if (!error)
                new_connection->read();
        }

        


        boost::asio::io_service& m_io_service;
        tcp_connection::pointer new_connection;
};

int main()
{
	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);
		
		tcp_client client(io_service, endpoint);
        client.send("teub");
		io_service.run();
        // client.send("Salam a toi\n");
        // io_service.
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
			
	return 0;
}