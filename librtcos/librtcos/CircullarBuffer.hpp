#pragma once

/**
 * @file CircullarBuffer.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-22
 */

#include <cstddef>
#include <librtcos/Queue.hpp>

namespace rtcos
{
	template <class T>
	class CircullarBuffer : public Queue<T>
	{
	public:
		CircullarBuffer(size_t, const T& initial = T());
		~CircullarBuffer();

		T get() override;
		bool put(T&) override;
		void remove(const T& = T()) override;

		bool isEmpty() override;
		bool isFull() override;

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