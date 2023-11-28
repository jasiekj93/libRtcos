#pragma once

/**
 * @file CircullarBuffer.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-22
 */

#include <cstddef>
#include <librtcos/Queue.hpp>

namespace rtcos::utils
{
	template <class T>
	class CircullarBuffer : public Queue<T>
	{
	public:
		CircullarBuffer(size_t, const T& nullValue = T());
		~CircullarBuffer();

		T get() const override;
		bool put(const T&) override;
		void remove() override;

		bool isEmpty() const override;
		bool isFull() const override;

        inline size_t getCount() const override { return count; }
        inline size_t getSize() const override { return size; }

	protected:
		void increment(size_t&);
		size_t putIndex;
		size_t getIndex;	
		size_t count;
		const size_t size;
		T* array;
        const T nullValue;

        CircullarBuffer(const CircullarBuffer&) = delete;
        CircullarBuffer(const CircullarBuffer&&) = delete;
        CircullarBuffer& operator=(const CircullarBuffer&) = delete;
        CircullarBuffer& operator=(const CircullarBuffer&&) = delete;
	};

}

#include <librtcos/utils/CircullarBuffer.tpp>