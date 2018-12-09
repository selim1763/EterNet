#pragma once
#include "Core.h"
#include <boost\asio.hpp>
#include <boost\thread\thread.hpp>
#include <boost\array.hpp>

namespace etn
{
	class ProcessFlow
	{
	protected:
		boost::asio::io_service m_recv_io_service;
		boost::asio::io_service m_send_io_service;
	private:
		boost::asio::io_service::work m_recv_work;
		boost::asio::io_service::work m_send_work;

		boost::thread_group m_recv_threadpool;
		boost::thread_group m_send_threadpool;
	private:
		boost::asio::io_service::strand m_recv_strand;
		boost::asio::io_service::strand m_send_strand;
	public:
		ProcessFlow();
		virtual ~ProcessFlow();
	public:
		virtual void DispatchRecv(const boost::array<uint8_t, MTU> buffer, const size_t transferred_bytes, const boost::asio::ip::udp::endpoint endpoint) = 0;
	public:
		boost::asio::io_service::strand * get_send_strand(){
			return &m_send_strand;
		}
		boost::asio::io_service::strand * get_recv_strand()	{
			return &m_recv_strand;
		}

	};
}