#pragma once

/**
 * @file LinkedList.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/Queue.hpp>
#include <cstddef>

namespace rtcos
{
    template<class T>
	class LinkedList : Queue<T>
	{
	public:
		LinkedList(size_t, const T& nullValue = T());
        ~LinkedList();

        T get() override;
		bool put(const T&) override;
		void remove() override;

		bool isEmpty() override;
		bool isFull() override;

    protected:
        struct Node
        {
            T value;
            bool isFree;
            Node* next;
        };

        Node* allocateNode(const T& value);
        void deallocateNode(Node*);
        void initalizeArray();

    private:
        size_t size;
        size_t count;
        Node* array;
        Node* head;
        Node* tail;
        T nullValue;
	};
}

#include <librtcos/LinkedList.tpp>