#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <string>
using boost::asio::ip::udp;

int main()
{
	boost::asio::io_service io;
	boost::asio::ip::udp::socket socket(io);

	
//	boost::asio::socket_base::broadcast option(true);
//	socket.set_option(option);
	

	boost::asio::ip::udp::endpoint target = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("10.1.15.22"), 7777);
	
	socket.open(udp::v4());
	while(true)
	{
		//socket.open(udp::v4());
		std::string send = "asdf";
		socket.send_to(boost::asio::buffer(send, send.size()), target);
		std::cout<<"Sending...";
	}
	return 0;
}

