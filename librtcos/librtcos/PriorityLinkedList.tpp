#pragma once

namespace rtcos
{
    template<class T>
    inline PriorityLinkedList<T>::PriorityLinkedList(size_t size,
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
    inline PriorityLinkedList<T>::~PriorityLinkedList()
    {
        delete[] array;
    }

    template<class T>
    inline T PriorityLinkedList<T>::get()
    {
        return (head ? head->value : nullValue);
    }

    template<class T>
    inline bool PriorityLinkedList<T>::put(const T& value, int priority)
    {
        if (isFull())
            return false;

        auto node = allocateNode(value, priority);
        assignPointers(node);
        return true;
    }

    template<class T>
    inline void PriorityLinkedList<T>::remove()
    {
        auto next = head->next;
        deallocateNode(head);
        head = (count == 0 ? nullptr : next);
    }

    template<class T>
    inline bool PriorityLinkedList<T>::isEmpty()
    {
        return (count == 0);
    }

    template<class T>
    inline bool PriorityLinkedList<T>::isFull()
    {
        return (count == size);
    }

    template<class T>
    inline typename PriorityLinkedList<T>::Node* PriorityLinkedList<T>::allocateNode(const T& value, int priority)
    {
        count++;
        for(auto i = 0U; i < size; i++)
        {
            if(array[i].isFree)
            {
                array[i].isFree = false;
                array[i].value = value;
                array[i].priority = priority;

                return &array[i];
            }
        }
        
        return nullptr;
    }

    template<class T>
    inline void PriorityLinkedList<T>::deallocateNode(Node* node)
    {
        count--;

        node->isFree = true;
        node->next = nullptr;
        node->value = nullValue;
    }

    template<class T>
    inline void PriorityLinkedList<T>::initalizeArray()
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

    template <class T>
    inline void PriorityLinkedList<T>::assignPointers(Node* node)
    {
        if(count == 1)
            head = node;
        else if (count == 2)
            assignPointersForTwoNodes(node);
        else
            assignPointersForMoreNodes(node);
    }

    template <class T>
    inline void PriorityLinkedList<T>::assignPointersForTwoNodes(Node* node)
    {
        if(head->priority >= node->priority)
            head->next = node;
        else
        {
            node->next = head;
            head = node;
        }
    }

    template <class T>
    inline void PriorityLinkedList<T>::assignPointersForMoreNodes(Node* node)
    {
        auto tmp = findNodeWithLowerPriority(node->priority);

        if(tmp->next == nullptr)
            tmp->next = node;
        else
        {
            node->next = tmp->next;
            tmp->next = node;
        }
    }

    template <class T>
    inline typename PriorityLinkedList<T>::Node* PriorityLinkedList<T>::findNodeWithLowerPriority(int priority)
    {
        auto tmp = head;
        while(tmp->next &&
            tmp->next->priority >= priority)
        {
            tmp = tmp->next;
        }

        return tmp;
    }
}
