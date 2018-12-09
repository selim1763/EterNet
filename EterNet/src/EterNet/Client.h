#pragma once

#include "Core.h"
#include <boost\asio.hpp>
#include <boost\array.hpp>
#include <string>

namespace etn
{
	class ClientHandler;

	class ETN_API Client
	{
	public:
		Client(const std::string & remote_ip,const unsigned short remote_port);
		virtual ~Client();
	public:
		virtual void OnMessage(const boost::asio::ip::udp::endpoint & endpoint, const boost::array<uint8_t, MTU> & buffer, const size_t & transferred_bytes) = 0;
	public:
		void Send(std::string message);
	private:
		boost::asio::io_service m_io_service;
		boost::asio::ip::udp::socket* m_socket;
		boost::array<uint8_t, MTU> m_recv_buffer;
	private:
		boost::asio::ip::udp::endpoint m_endpoint;
		boost::asio::ip::udp::endpoint remote_endpoint;
	private:
		ClientHandler* m_ptr_handler;
	private:
		void Handle_Recv(const boost::system::error_code & error, size_t actual_bytes);
		void StartReceive();
		void Handle_Send(const boost::system::error_code & error, size_t actual_bytes);
	};

}