#include "ClientSession.h"
#include "ServerHandler.h"
#include <iostream>

namespace etn
{
	ClientSession::ClientSession(ServerHandler * process_handler, boost::asio::ip::udp::endpoint & endpoint)
		: m_ptr_handler(process_handler),
		m_timer_timeout(process_handler->get_send_strand()->get_io_service()),
		m_endpoint(endpoint)
	{
	}

	ClientSession::~ClientSession()
	{
	}

	void ClientSession::StartTimer()
	{
		auto timer = m_timer_timeout.get_timer();

		timer->expires_from_now(boost::posix_time::milliseconds(TIMER_INTERVAL));

		timer->async_wait(m_ptr_handler->get_send_strand()->wrap(boost::bind(
			&ClientSession::DispatchTimer, this, boost::asio::placeholders::error)));
	}

	void ClientSession::DispatchTimer(const boost::system::error_code & error)
	{
		if (!error || error != boost::asio::error::operation_aborted)
			HandleTimer();
		else
			std::cout << __FUNCTION__ << " Error -> " << error.message() << std::endl;
	}

	void ClientSession::HandleTimer()
	{
		m_time.fetch_add(1, std::memory_order_relaxed);

		if (m_time.load(std::memory_order_acquire) < TIME_OUT_SEC)
		{
			StartTimer();
		}
		else
		{
			m_timer_timeout.get_timer()->cancel();
			m_ptr_handler->OnClientTimeOut(m_endpoint);
			/*
				should we trigger it ? think we should cause we shouldnt wait  for clients to send packages
			*/
		}
	}

	void ClientSession::reset_time()
	{
		m_time.store(0, std::memory_order_release);
	}
}