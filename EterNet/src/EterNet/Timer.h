#pragma once
#include <stdint.h>
#include <boost\asio\deadline_timer.hpp>

namespace etn
{
	class Timer
	{
	private:
		boost::asio::deadline_timer timer;
	public:
		Timer(boost::asio::io_service & io_service)
			: timer(io_service)
		{
		}
		~Timer() {}
	public:
		boost::asio::deadline_timer * get_timer() { return &timer; }
	};
}