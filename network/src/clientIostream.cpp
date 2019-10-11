#include <iostream>
#include <string>
#include <boost/asio.hpp>

void run(boost::asio::ip::tcp::iostream* s)
{
    std::string str;

    while (std::getline(*s, str)) {
        std::cout << "msg : " << str << std::endl;
    }
}

int main(int ac, char **arg)
{
    boost::asio::ip::tcp::iostream* s = new boost::asio::ip::tcp::iostream(/* "10.101.53.32" */ /* "109.22.211.146", "27018" */ "10.101.52.141", arg[1]); //(1)
    std::string line;
    std::string str;

    std::getline(*s, str);
    std::cout << "msg : " << str << std::endl;
    if (str == "") {
        std::cout << "ERROR CONNECTION" << std::endl;
        return 0;
    }


    // std::cout << "START" << std::endl;
    std::thread _tone = std::thread([s]() {run(s);});

    while (str.compare("QUIT") != false) {
        std::getline(std::cin, str);
        *s << str << std::endl;
    }

    _tone.join();
    return 0;
}