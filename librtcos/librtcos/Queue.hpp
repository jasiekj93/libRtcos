#pragma once

/**
 * @file Queue.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-22
 */

namespace rtcos
{
	template <class T>
	class Queue
	{
	public:
		virtual ~Queue() {};

		virtual T get() = 0;
		virtual bool put(T&) = 0;
		virtual void remove(const T& replacement = T()) = 0;

		virtual bool isEmpty() = 0;
		virtual bool isFull() = 0;
	};
}
