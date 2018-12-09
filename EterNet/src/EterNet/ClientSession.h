#pragma once
#include "Timer.h"
#include <boost\asio.hpp>

namespace etn
{
	#define TIMER_INTERVAL 1000
	#define TIME_OUT_SEC 5
	//----

	class ServerHandler;

	class ClientSession
	{
	public:
		ClientSession(ServerHandler * process_handler, boost::asio::ip::udp::endpoint & endpoint);
		~ClientSession();
	private:
		ServerHandler* m_ptr_handler;
		Timer m_timer_timeout;
		std::atomic<unsigned char> m_time{ 0 };
	private:
		boost::asio::ip::udp::endpoint m_endpoint;
	public:
		void reset_time();
	private:
		void StartTimer();
		void DispatchTimer(const boost::system::error_code & error);
		void HandleTimer();
	};
}