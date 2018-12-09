#include "ClientHandler.h"
#include "Client.h"

namespace etn
{
	ClientHandler::ClientHandler(Client * client) : client(client)
	{
	}

	void ClientHandler::DispatchRecv(const boost::array<uint8_t, MTU> buffer, const size_t transferred_bytes, const boost::asio::ip::udp::endpoint endpoint)
	{
		client->OnMessage(endpoint, buffer, transferred_bytes);
	}

}