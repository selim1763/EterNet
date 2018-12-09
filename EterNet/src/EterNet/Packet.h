#pragma once
#include "ByteBuffer.h"
#include <boost\array.hpp>

namespace etn
{
	namespace Stream
	{
		template<typename T>
		inline void Write(ByteBuffer & b, T & value)
		{
			*((T*)(b.data + b.index)) = value;
			b.index += sizeof(T);
		}

		template<typename T>
		inline void Write(ByteBuffer & b, const T & value)
		{
			*((T*)(b.data + b.index)) = value;
			b.index += sizeof(T);
		}

		template<typename T>
		inline void Read(const boost::array<uint8_t, MTU> & b, uint16_t & index, T & value)
		{
			value = *((T*)(b.data() + index));
			index += sizeof(T);
		}
		//-------------------------------------------
		//-------------------------------------------
		void WriteString(ByteBuffer & b, const char* value);
		char* ReadString(const boost::array<uint8_t, MTU> & b, uint16_t & index);
	}

}




