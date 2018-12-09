#include "EterNet\Server.h"
#include <iostream>

#define EP(x) "["+x.address().to_string()+":"+std::to_string(x.port())+"]:"

class Server : public etn::Server
{
public:
	Server()
	{
	}
	~Server()
	{
	}
	//-----------------------
	//-----------------------
	void OnConnection(const boost::asio::ip::udp::endpoint & endpoint) 
	{
		std::cout << EP(endpoint) << " Connected." << std::endl;
	}

	void OnMessage(const boost::asio::ip::udp::endpoint & endpoint, const boost::array<uint8_t, MTU> & buffer, const size_t & transferred_bytes)
	{
		std::string message(buffer.begin(), buffer.begin() + transferred_bytes);

		std::cout << EP(endpoint) << " "+ message << std::endl;
	
		this->Send(message + " mesajini aldim :)", endpoint);
	}

	void OnExit(const boost::asio::ip::udp::endpoint & endpoint) 
	{
		std::cout << EP(endpoint) << " Has lost connection." << std::endl;
	}
};


void main()
{
	Server* server = new Server();
	server->Run(8888);
}