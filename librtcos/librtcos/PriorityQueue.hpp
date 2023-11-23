#pragma once

/**
 * @file PriorityQueue.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-22
 */

namespace rtcos
{
	template <class T>
	class PriorityQueue
	{
	public:
		virtual ~PriorityQueue() {};

		virtual T get() = 0;
		virtual bool put(const T&, int priority = 0) = 0;
		virtual void remove() = 0;

		virtual bool isEmpty() = 0;
		virtual bool isFull() = 0;
	};
}