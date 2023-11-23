#pragma once

namespace rtcos
{
    template<class T>
    inline LinkedList<T>::LinkedList(size_t size,
        const T& nullValue)
        : size(size)
        , count(0)
        , head(nullptr)
        , array(nullptr)
        , nullValue(nullValue)
    {
        array = new Node[size];
        initalizeArray();
    }

    template<class T>
    inline LinkedList<T>::~LinkedList()
    {
        delete[] array;
    }

    template<class T>
    inline T LinkedList<T>::get()
    {
        return (head ? head->value : nullValue);
    }

    template<class T>
    inline bool LinkedList<T>::put(const T& value)
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

    template<class T>
    inline void LinkedList<T>::remove()
    {
        auto next = head->next;
        deallocateNode(head);

        if(count == 0)
            head = tail = nullptr;
        else
            head = next;
    }

    template<class T>
    inline bool LinkedList<T>::isEmpty()
    {
        return (count == 0);
    }

    template<class T>
    inline bool LinkedList<T>::isFull()
    {
        return (count == size);
    }

    template<class T>
    inline typename LinkedList<T>::Node* LinkedList<T>::allocateNode(const T& value)
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

    template<class T>
    inline void LinkedList<T>::deallocateNode(Node* node)
    {
        count--;

        node->isFree = true;
        node->next = nullptr;
        node->value = nullValue;
    }

    template<class T>
    inline void LinkedList<T>::initalizeArray()
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