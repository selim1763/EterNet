#pragma once
#include "ProcessFlow.h"

namespace etn
{
	class Client;

	class ClientHandler : public ProcessFlow
	{
	public:
		ClientHandler(Client * client);
	public:
		void DispatchRecv(const boost::array<uint8_t, MTU> buffer, const size_t transferred_bytes, const boost::asio::ip::udp::endpoint endpoint);
	private:
		Client* client;
	};


}
