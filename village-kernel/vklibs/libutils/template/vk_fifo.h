//###########################################################################
// vk_fifo.h
// Declarations of the functions that manage fifo
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_FIFO_H__
#define __VK_FIFO_H__

#include "stdint.h"


/// @brief Fifo
template<typename Object>
class Fifo
{
private:
	/// @brief Members
	int writeIndex;
	int readIndex;
	int prevDataIndex;
	int dataLength;
	int bufferSize;
	Object *dataBuffer;
public:
	/// @brief Setup
	/// @param size 
	void Setup(int size)
	{
		writeIndex = 0;
		readIndex = 0;
		prevDataIndex = 0;
		dataLength = 0;
		bufferSize = size;
		dataBuffer = new Object[size]();
	}


	/// @brief Put data into fifo buffer
	/// @param data 
	/// @param size 
	int Put(Object *data, int size)
	{
		for (int index = 0; index < size; index++)
		{
			dataBuffer[writeIndex] = data[index];

			if (++writeIndex >= bufferSize) writeIndex = 0;
		}

		dataLength += size;

		return size;
	}


	/// @brief Pop data from fifo buffer
	/// @param data 
	/// @param size 
	int Pop(Object *data, int size)
	{
		for (int index = 0; index < size; index++)
		{
			if (dataLength <= 0) return index;

			data[index] = dataBuffer[readIndex];

			if (dataLength)
			{
				if (++readIndex >= bufferSize) readIndex = 0;
				--dataLength;
			}
		}

		return size;
	}


	/// @brief Exit
	void Exit()
	{
		delete[] dataBuffer;
	}
};

#endif //!__VK_FIFO_H__
