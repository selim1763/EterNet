#include "Packet.h"

namespace etn
{
	///
	namespace Stream
	{
		void WriteString(ByteBuffer & b, const char* value)
		{
			uint16_t size = strlen(value);
			*((uint16_t*)(b.data + b.index)) = size;
			b.index += 2;

			memcpy(&b.data[b.index], (uint8_t*)value, size);

			b.index += size;
		}
		char* ReadString(const boost::array<uint8_t, MTU> & b, uint16_t & index)
		{
			uint16_t size = *((uint16_t*)(b.data() + Channel::Incoming_Packet::index));
			Channel::Incoming_Packet::index += 2;

			memcpy(Channel::Incoming_Packet::string_read_buffer + index,
				(char*)b.data() + Channel::Incoming_Packet::index, size);
			*(Channel::Incoming_Packet::string_read_buffer + index + size) = '\0';

			Channel::Incoming_Packet::index += size;

			char* start_pointer = (Channel::Incoming_Packet::string_read_buffer + index);
			index += size + 1;
			return start_pointer;
		}
	}

}