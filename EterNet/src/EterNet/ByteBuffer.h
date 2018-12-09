#pragma once
#include "Core.h"
#include <stdint.h>
#include <memory>

struct ByteBuffer
{
	uint8_t* buffer;
	uint8_t* data;
	uint16_t index = 0;
	uint16_t buffer_length = 0;

	inline void Flush()
	{
		index = 0;
	}

	ByteBuffer() {
		buffer_length = MTU;
		buffer = new uint8_t[MTU];
		data = buffer;
	}

	ByteBuffer(uint16_t & buff_len) {
		buffer_length = buff_len;
		buffer = new uint8_t[buff_len];
		data = buffer;
	}

	ByteBuffer(const ByteBuffer & buff)
	{
		//Deep copy
		memcpy(buffer, buff.data, buff.index);

		index = buff.index;
		buffer_length = buff.buffer_length;
	}
	ByteBuffer& operator = (const ByteBuffer & buff)
	{
		memcpy(buffer, buff.data, buff.index);

		index = buff.index;
		buffer_length = buff.buffer_length;

		return *this;
	}

	~ByteBuffer()
	{
		delete[] buffer;
	}
};


