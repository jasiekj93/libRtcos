#pragma once

/**
 * @file LinkedList.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/Queue.hpp>
#include <librtcos/MemoryPool.hpp>

namespace rtcos
{
    template<class T>
	class LinkedList : public Queue<T>
	{
	public:
		LinkedList(size_t, const T& nullValue = T());

        T get() const override;
		bool put(const T&) override;
		void remove() override;

		inline bool isEmpty() const override { return pool.isEmpty(); }
		inline bool isFull() const override { return pool.isFull(); }

        inline size_t getCount() const override { return pool.getCount(); }
        inline size_t getSize() const override { return pool.getSize(); }

    protected:
        struct Node
        {
            T value;
            Node* next;
        };

    private:
        MemoryPool<Node> pool;
        Node* head;
        Node* tail;
	};
}

#include <librtcos/LinkedList.tpp>