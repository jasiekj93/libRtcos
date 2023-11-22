#pragma once

/**
 * @file CircullarBuffer.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-22
 */

#include <cstddef>

namespace rtcos
{
	template <class T>
	class CircullarBuffer
	{
	public:
		CircullarBuffer(size_t);
		~CircullarBuffer();

		T get();
		bool put(T&);
		void remove();

		bool isEmpty();
		bool isFull();

	protected:
		void increment(size_t&);
		size_t putIndex;
		size_t getIndex;	
		size_t count;
		size_t size;
		T* array;
	};

}

#include <librtcos/CircullarBuffer.tpp>