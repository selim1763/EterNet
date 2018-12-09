#include "ServerHandler.h"
#include "Server.h"
#include "ClientSession.h"
#include <boost/unordered_map.hpp>

// Endpoint to hash 
namespace boost
{
	template <>
	struct hash<asio::ip::udp::endpoint>
	{
		size_t operator()(asio::ip::udp::endpoint const& v) const {

			unsigned long x = v.address().to_v4().to_ulong() + v.port();
			return hash_value(x);
		}
	};
}

namespace etn
{
	boost::unordered::unordered_map<boost::asio::ip::udp::endpoint, ClientSession*> map_sessions;
}

namespace etn
{
	ServerHandler::ServerHandler(Server * server)
		:server(server)
	{
	}


	void ServerHandler::DispatchRecv(const boost::array<uint8_t, MTU> buffer, const size_t transferred_bytes, const boost::asio::ip::udp::endpoint endpoint)
	{

		if (map_sessions.find(endpoint) != map_sessions.end())
		{
			auto client_session = map_sessions[endpoint];
			client_session->reset_time();
			

		}
		else
		{
		}
		/*
			Bu endpoint daha önce bizle baðlantý kurdu mu ?

			kurmadýysa baðlantý kuracak, ConnectionTimeOut'da ise Exit ile çýkýþ yapacak.
		
			gelen endpoint ile client sýnýfýný map'le bu client sýnýfýn da timer'ý olucak.



			if(!hashtableContains)
			{
				new ClientSession
				hastable.add(client_session);
				server->OnConnection(...);
			}
			else
			{
				client_session = hastable[endpoint];
				client_session.reset_timeout();

				if(its not alive packet)
					server->OnMessage(endpoint, buffer, transferred_bytes);
				
			}


		*/


		server->OnMessage(endpoint, buffer, transferred_bytes);
	}

	void etn::ServerHandler::OnClientTimeOut(boost::asio::ip::udp::endpoint & endpoint)
	{
		/*
			Clean Up.		
		*/
		server->OnExit(endpoint);
	}

}