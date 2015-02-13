#include <boost/array.hpp>
#include <boost/asio.hpp> //network library for TCP and UDP
#include "UDPSend.h"

using boost::asio::ip::udp;

bool UDPSend(char* sAddress, int iPort, char* sData)
{
        try
        {
                boost::asio::io_service io; //All io operations need this
                boost::asio::ip::udp::endpoint target = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(sAddress), iPort);//Creates a destination object with iPort as the Port to use and sAddress as it's IP Address
                boost::asio::ip::udp::socket socket(io); //Opens a socket using the io object to perform input output operations
                socket.open(udp::v4()); //Opens a socket on UDP over IPV4
                socket.send_to(boost::asio::buffer(sData, sizeof(sData)), target);
        }
        catch (std::exception &e) //Member functions of asio may throw errors and this catches them
        {
                std::cerr<<e.what()<<std::endl;
                return true; //If catch runs, a throw() function ran and an error occured. 
        }
        return false; //If it passes the catch block, no errors occured.
}
