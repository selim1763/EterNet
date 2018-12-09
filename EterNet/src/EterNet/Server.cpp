#include <boost\bind.hpp>
#include "Server.h"
#include "ServerHandler.h"
#include <iostream>


namespace etn
{
	//GLOBAL DECLARATIONS
	boost::mutex global_lock;
	//boost::unordered::unordered_map<boost::asio::ip::udp::endpoint, Client*  > global_map_clients;
	//
}


namespace etn
{
	Server::Server()
	{
	}

	Server::~Server()
	{}

	void Server::Run(const unsigned short port)
	{
		m_socket = new boost::asio::ip::udp::socket(m_io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
		m_work = new boost::asio::io_service::work(m_io_service);
		m_ptr_handler = new etn::ServerHandler(this);
	 

		StartReceive();

		m_io_service.run();
	}

	void Server::Send(std::string message, const boost::asio::ip::udp::endpoint & endpoint)
	{
		auto _message = message.c_str();

		m_socket->async_send_to(
			boost::asio::buffer(_message, strlen(_message)),
			endpoint,
			m_ptr_handler->get_send_strand()->wrap(boost::bind(&Server::Handle_Send, this, boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred))
		);
	}

	void Server::Handle_Send(const boost::system::error_code & error, size_t actual_bytes)
	{
		if (error)
			std::cout << __FUNCTION__ << "-ERROR -> " << error.message() << std::endl;

	}


	void Server::Handle_Recv(const boost::system::error_code & error, size_t actual_bytes) 
	{
		//eðer gelen paket boyutu buffer'dan büyükse
		if (!error || error == boost::asio::error::message_size)
		{

			m_ptr_handler->get_recv_strand()->post(boost::bind(
				&ServerHandler::DispatchRecv,
				m_ptr_handler,
				m_recv_buffer,
				actual_bytes,
				m_endpoint
			));

		}

		StartReceive();
		//Start next receive

		//auto k = m_endpoint.address().to_v4().to_bytes();
	}

	void Server::StartReceive()
	{
		m_socket->async_receive_from(
			boost::asio::buffer(m_recv_buffer),
			m_endpoint,
			boost::bind(&Server::Handle_Recv, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
}