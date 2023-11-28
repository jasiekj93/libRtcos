#pragma once

/**
 * @file PriorityLinkedList.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/PriorityQueue.hpp>
#include <librtcos/utils/MemoryPool.hpp>

namespace rtcos::utils
{
    template<class T>
	class PriorityLinkedList : public PriorityQueue<T>
	{
	public:
		PriorityLinkedList(size_t, const T& nullValue = T());

        T get() const override;
		bool put(const T&, int priority = 0) override;
		void remove() override;

		inline bool isEmpty() const override { return pool.isEmpty(); }
		inline bool isFull() const override { return pool.isFull(); }

    protected:
        struct Node
        {
            T value;
            int priority;
            Node* next;
        };

        void assignPointers(Node* newNode);
        void assignPointersForTwoNodes(Node* newNode);
        void assignPointersForMoreNodes(Node* newNode);
        Node* findNodeWithLowerPriority(int priority) const;

    private:
        utils::MemoryPool<Node> pool; 
        Node* head;
	};
}

#include <librtcos/utils/PriorityLinkedList.tpp>
