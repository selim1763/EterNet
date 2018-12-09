#include "EterNet\Client.h"
#include <iostream>

#define EP(x) "["+x.address().to_string()+":"+std::to_string(x.port())+"]:"

class Client : public etn::Client
{
public:
	Client(const std::string remote_ip,
		const unsigned short remote_port) : etn::Client(remote_ip, remote_port)
	{}
	~Client()
	{}

	void OnMessage(const boost::asio::ip::udp::endpoint & endpoint, const boost::array<uint8_t, MTU> & buffer, const size_t & transferred_bytes)
	{
		std::string message(buffer.begin(), buffer.begin() + transferred_bytes);

		std::cout << EP(endpoint) << " " + message << std::endl;
	}
};

void main()
{
	Client* client = new Client("127.0.0.1", 8888);
	client->Send("Selam");

	while (true);
 
}