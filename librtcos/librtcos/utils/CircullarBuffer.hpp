#pragma once

/**
 * @file CircullarBuffer.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-22
 */

#include <cstddef>
#include <librtcos/Queue.hpp>
#include <memory>

namespace rtcos::utils
{
	template <class T>
	class CircullarBuffer : public Queue<T>
	{
	public:
		CircullarBuffer(size_t, const T& nullValue = T());

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
		std::unique_ptr<T[]> array;
        const T nullValue;
	};

}

#include <librtcos/utils/CircullarBuffer.tpp>