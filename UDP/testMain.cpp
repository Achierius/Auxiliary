#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "UDPSend.h"

using namespace std;
using boost::asio::ip::udp;

//bool UDPSend(char* sAddress, int iPort, char* sData)
//{return true;}
int main(int argc, char* argv[])
{
	boost::asio::io_service io;
	if(argc == 3) //Programname, IP, Port
	{
		std::cout<<"Input Data to Send: \n";
		char* pTcData;
		std::cin>>pTcData;
		std::cout<<"Sending "<<pTcData<<" to "<<argv[1]<<" on their port number"<<argv[2]<<".\n";
		while(!UDPSend(argv[1], boost::lexical_cast<int>(argv[2]), pTcData))
		{
			boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(20));
                        t.wait();
		}
		return 0;
	}
	else if(argc == 4) //Programname, IP, Port, Data
	{
		std::cout<<"Sending "<<argv[3]<<" to "<<argv[1]<<" on their port number"<<argv[2]<<".\n";
                while(!UDPSend(argv[1], boost::lexical_cast<int>(argv[2]), argv[3]))
                {
                        boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(20));
                        t.wait();
                }
		return 0;

	}
	else if(argc == 0)
	{
		std::cout<<"Input Data to Send: \n";
                char* pTcData;
                std::cin>>pTcData;
		std::cout<<"Input Port Number: \n";
		int iPort;
		std::cin>>iPort;
		std::cout<<"Input IP Address to send to: \n";
		char* pTcIP;
		std::cin>>pTcIP;
                std::cout<<"Sending "<<pTcData<<" to "<<pTcIP<<" on their port number"<<iPort<<".\n";
                while(!UDPSend(argv[1], boost::lexical_cast<int>(argv[2]), pTcData))
                {
                        boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(20));
                        t.wait();
                }
                return 0;

	}
	else
	{
		std::cout<<"Format: Any of \nUDPSend <IP> <Port>\nUDPSend <IP> <Port> <Data>\nUDPSend\n\n";
		std::cout<<"Press Enter to exit...\n";
		int i; //i was sleepy and too lazy to do nthis nicely
		std::cin>>i;
	}
	
	return 0;
}
