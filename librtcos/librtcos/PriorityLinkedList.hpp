#pragma once

/**
 * @file PriorityLinkedList.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/PriorityQueue.hpp>
#include <cstddef>

namespace rtcos
{
    template<class T>
	class PriorityLinkedList : public PriorityQueue<T>
	{
	public:
		PriorityLinkedList(size_t, const T& nullValue = T());
        ~PriorityLinkedList();

        T get() const override;
		bool put(const T&, int priority = 0) override;
		void remove() override;

		bool isEmpty() const override;
		bool isFull() const override;

    protected:
        struct Node
        {
            T value;
            int priority;
            bool isFree;
            Node* next;
        };

        Node* allocateNode(const T& value, int priority);
        void deallocateNode(Node*);
        void initalizeArray();
        void assignPointers(Node* newNode);
        void assignPointersForTwoNodes(Node* newNode);
        void assignPointersForMoreNodes(Node* newNode);
        Node* findNodeWithLowerPriority(int priority) const;

    private:
        size_t size;
        size_t count;
        Node* array;
        Node* head;
        T nullValue;
	};
}

#include <librtcos/PriorityLinkedList.tpp>
