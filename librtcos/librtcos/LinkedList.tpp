#pragma once

namespace rtcos
{
    template<class T>
    inline LinkedList<T>::LinkedList(size_t size,
        const T& nullValue)
        : pool(size, { .value = nullValue, .next = nullptr })
        , head(nullptr)
        , tail(nullptr)
    {
    }

    template<class T>
    inline T LinkedList<T>::get() const
    {
        return (head ? head->value : pool.getNullValue().value);
    }

    template<class T>
    inline bool LinkedList<T>::put(const T& value)
    {
        auto node = pool.allocate({ .value = value, .next = nullptr });

        if (node == nullptr)
            return false;

        if(pool.getCount() > 1)
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
        pool.deallocate(head);

        if(pool.isEmpty())
            head = tail = nullptr;
        else
            head = next;
    }
}