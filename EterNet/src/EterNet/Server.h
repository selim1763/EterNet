#pragma once

#include "Core.h"
#include <boost\asio.hpp>
#include <boost\array.hpp>

namespace etn
{
	class ServerHandler;

	class ETN_API Server
	{
	public:
		Server();
		virtual ~Server();
	public:
		void Run(const unsigned short port);
	public:
		virtual void OnConnection(const boost::asio::ip::udp::endpoint & endpoint) = 0;
		virtual void OnMessage(const boost::asio::ip::udp::endpoint & endpoint, const boost::array<uint8_t, MTU> & buffer, const size_t & transferred_bytes) = 0;
		virtual void OnExit(const boost::asio::ip::udp::endpoint & endpoint) = 0;
	public:
		void Send(std::string message, const boost::asio::ip::udp::endpoint & endpoint);
	private:
		boost::asio::io_service m_io_service;
		boost::asio::ip::udp::socket* m_socket;
		boost::asio::io_service::work* m_work;
		boost::asio::ip::udp::endpoint m_endpoint;
		boost::array<uint8_t, MTU> m_recv_buffer;
	private:
		ServerHandler* m_ptr_handler;
	private:
		void Handle_Recv(const boost::system::error_code & error, size_t actual_bytes);
		void StartReceive();
		void Handle_Send(const boost::system::error_code & error, size_t actual_bytes);
	};

}