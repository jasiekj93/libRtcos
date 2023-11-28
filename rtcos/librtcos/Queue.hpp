#pragma once

/**
 * @file Queue.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-22
 */

#include <cstddef>

namespace rtcos
{
	template <class T>
	class Queue
	{
	public:
		virtual ~Queue() {};

		virtual T get() const = 0;
		virtual bool put(const T&) = 0;
		virtual void remove() = 0;

		virtual bool isEmpty() const = 0;
		virtual bool isFull() const = 0;

        virtual size_t getCount() const = 0;
        virtual size_t getSize() const = 0;
	};
}
