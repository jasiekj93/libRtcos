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
	class PriorityLinkedList : PriorityQueue<char>
	{
	public:
		PriorityLinkedList(size_t, const char& nullValue = char());
        ~PriorityLinkedList();

        char get() override;
		bool put(char&, int priority = 0) override;
		void remove(const char& replacement = char()) override;

		bool isEmpty() override;
		bool isFull() override;

    protected:
        struct Node
        {
            char value;
            int priority;
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


    inline PriorityLinkedList::PriorityLinkedList(size_t size,
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

    inline PriorityLinkedList::~PriorityLinkedList()
    {
        delete[] array;
    }

    inline char PriorityLinkedList::get()
    {
        return (head ? head->value : nullValue);
    }

    inline bool PriorityLinkedList::put(char& value, int priority)
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

    inline void PriorityLinkedList::remove(const char &replacement)
    {
        auto next = head->next;
        deallocateNode(head);

        if(count == 0)
            head = tail = nullptr;
        else
            head = next;
    }

    inline bool PriorityLinkedList::isEmpty()
    {
        return (count == 0);
    }

    inline bool PriorityLinkedList::isFull()
    {
        return (count == size);
    }

    inline PriorityLinkedList::Node* PriorityLinkedList::allocateNode(char &value)
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

    inline void PriorityLinkedList::deallocateNode(Node* node)
    {
        count--;

        node->isFree = true;
        node->next = nullptr;
        node->value = nullValue;
    }

    inline void PriorityLinkedList::initalizeArray()
    {
        for(auto i = 0U; i < size; i++)
        {
            array[i] = {
                .value = nullValue,
                .priority = 0,
                .isFree = true,
                .next = nullptr
            };
        }
    }

}
