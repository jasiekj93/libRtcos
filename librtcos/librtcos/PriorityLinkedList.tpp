#pragma once

namespace rtcos
{
    template<class T>
    inline PriorityLinkedList<T>::PriorityLinkedList(size_t size,
        const T& nullValue)
        : pool(size, { .value = nullValue, .priority = 0, .next = nullptr })
        , head(nullptr)
    {
    }

    template<class T>
    inline T PriorityLinkedList<T>::get() const 
    {
        return (head ? head->value : pool.getNullValue().value );
    }

    template<class T>
    inline bool PriorityLinkedList<T>::put(const T& val, int prio)
    {
        auto node = pool.allocate({ .value = val, .priority = prio, .next = nullptr });

        if (node == nullptr)
            return false;

        assignPointers(node);
        return true;
    }

    template<class T>
    inline void PriorityLinkedList<T>::remove()
    {
        if(isEmpty())
            return;

        auto next = (head->next ? head->next : nullptr);
        pool.deallocate(head);
        head = next;
    }

    template <class T>
    inline void PriorityLinkedList<T>::assignPointers(Node* node)
    {
        if(pool.getCount() == 1)
            head = node;
        else if (pool.getCount() == 2)
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
    inline typename PriorityLinkedList<T>::Node* PriorityLinkedList<T>::findNodeWithLowerPriority(int priority) const
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
