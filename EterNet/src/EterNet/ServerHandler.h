#pragma once
#include "ProcessFlow.h"
 
namespace etn
{
	class Server;

	class ServerHandler : public ProcessFlow
	{
	public:
		ServerHandler(Server* server); 
	public:
		void DispatchRecv(const boost::array<uint8_t, MTU> buffer, const size_t transferred_bytes, const boost::asio::ip::udp::endpoint endpoint);
	public:
		void OnClientTimeOut(boost::asio::ip::udp::endpoint & endpoint);
	private:
		Server* server;
	};


}

 