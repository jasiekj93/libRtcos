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
	class LinkedList : public Queue<T>
	{
	public:
		LinkedList(size_t, const T& nullValue = T());
        ~LinkedList();

        T get() const override;
		bool put(const T&) override;
		void remove() override;

		bool isEmpty() const override;
		bool isFull() const override;

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
        const size_t size;
        size_t count;
        Node* array;
        Node* head;
        Node* tail;
        T nullValue;

        LinkedList(const LinkedList&) = delete;
        LinkedList(const LinkedList&&) = delete;
        LinkedList& operator=(const LinkedList&) = delete;
        LinkedList& operator=(const LinkedList&&) = delete;
	};
}

#include <librtcos/LinkedList.tpp>