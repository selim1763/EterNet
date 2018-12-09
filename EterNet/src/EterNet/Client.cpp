#include "Client.h"
#include "ClientHandler.h"
#include <iostream>

namespace etn
{
	Client::Client(const std::string & remote_ip, const unsigned short remote_port):
		remote_endpoint(boost::asio::ip::address::from_string(remote_ip), remote_port)
	{
		m_socket = new boost::asio::ip::udp::socket(m_io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));

		m_ptr_handler = new ClientHandler(this);
		
		StartReceive();

		boost::thread run_thread(boost::bind(&boost::asio::io_service::run, boost::ref(m_io_service)));
	}

	Client::~Client()
	{}

	void Client::Send(std::string message)
	{
		auto _message = message.c_str();

		m_socket->async_send_to(
			boost::asio::buffer(_message, strlen(_message)),
			remote_endpoint,
			m_ptr_handler->get_send_strand()->wrap(boost::bind(&Client::Handle_Send, this, boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred))
		);
	}

	void Client::Handle_Send(const boost::system::error_code & error, size_t actual_bytes)
	{
		if (error)
			std::cout << __FUNCTION__ << "-ERROR -> " << error.message() << std::endl;
 
	}

	void Client::Handle_Recv(const boost::system::error_code & error, size_t actual_bytes)
	{
		//eðer gelen paket boyutu buffer'dan büyükse
		if (!error || error == boost::asio::error::message_size)
		{

			m_ptr_handler->get_send_strand()->post(boost::bind(
				&ClientHandler::DispatchRecv,
				m_ptr_handler,
				m_recv_buffer,
				actual_bytes,
				m_endpoint
			));

		}

		StartReceive();
	}

	void Client::StartReceive()
	{
		m_socket->async_receive_from(
			boost::asio::buffer(m_recv_buffer),
			m_endpoint,
			boost::bind(&Client::Handle_Recv, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}

}