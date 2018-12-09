#include "ProcessFlow.h"
#include <iostream>

namespace etn
{
	ProcessFlow::ProcessFlow()
		: m_recv_strand(m_recv_io_service), m_recv_work(m_recv_io_service), m_send_strand(m_send_io_service), m_send_work(m_send_io_service)
	{
		for (unsigned short i = 0; i < 2; i++)
		{
			m_recv_threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &m_recv_io_service));
		}
		std::cout << "[Processor]Receiver io_service hazir." << std::endl;

		//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

		for (unsigned short i = 0; i < 2; i++)
		{
			m_send_threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &m_send_io_service));
		}
		std::cout << "[Processor]Sender io_service hazir." << std::endl;

		//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	}

	ProcessFlow::~ProcessFlow()
	{
	}
 



}