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
	class LinkedList : Queue<char>
	{
	public:
		LinkedList(size_t, const char& nullValue = char());
        ~LinkedList();

        char get() override;
		bool put(char&) override;
		void remove() override;

		bool isEmpty() override;
		bool isFull() override;

    protected:
        struct Node
        {
            char value;
            bool isFree;
            Node* next;
        };

        Node* allocateNode(char& value);
        void deallocateNode(Node*);
        void initalizeArray();

    private:
        size_t size;
        size_t count;
        Node* array;
        Node* head;
        Node* tail;
        char nullValue;
	};


    inline LinkedList::LinkedList(size_t size,
        const char& nullValue)
        : size(size)
        , count(0)
        , head(nullptr)
        , array(nullptr)
        , nullValue(nullValue)
    {
        array = new Node[size];
        initalizeArray();

    }

    inline LinkedList::~LinkedList()
    {
        delete[] array;
    }

    inline char LinkedList::get()
    {
        return (head ? head->value : nullValue);
    }

    inline bool LinkedList::put(char& value)
    {
        if (isFull())
            return false;

        auto node = allocateNode(value);

        if(count > 1)
            tail->next = node;
        else
            head = node;

        tail = node;
        return true;
    }

    inline void LinkedList::remove()
    {
        auto next = head->next;
        deallocateNode(head);

        if(count == 0)
            head = tail = nullptr;
        else
            head = next;
    }

    inline bool LinkedList::isEmpty()
    {
        return (count == 0);
    }

    inline bool LinkedList::isFull()
    {
        return (count == size);
    }

    inline LinkedList::Node* LinkedList::allocateNode(char &value)
    {
        count++;
        for(auto i = 0U; i < size; i++)
            if(array[i].isFree)
            {
                array[i].isFree = false;
                array[i].value = value;

                return &array[i];
            }
        
        return nullptr;
    }

    inline void LinkedList::deallocateNode(Node* node)
    {
        count--;

        node->isFree = true;
        node->next = nullptr;
        node->value = nullValue;
    }

    inline void LinkedList::initalizeArray()
    {
        for(auto i = 0U; i < size; i++)
        {
            array[i] = {
                .value = nullValue,
                .isFree = true,
                .next = nullptr
            };
        }
    }

}