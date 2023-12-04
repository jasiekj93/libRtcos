#pragma once

namespace rtcos::utils
{
    template<class T>
    inline MemoryPool<T>::MemoryPool(size_t s, const T& nullValue)
        : size(s)
        , count(0)
        , array(std::make_unique<Segment[]>(s))
        , nullValue(nullValue)
    {
        for(auto i = 0U; i < size; i++)
        {
            array[i] = {
                .value = nullValue,
                .isFree = true
            };
        }
    }

    template <class T>
    inline T* MemoryPool<T>::allocate(const T& value)
    {
        if(isFull())
            return nullptr;

        for(auto i = 0U; i < size; i++)
            if(array[i].isFree)
            {
                array[i].isFree = false;
                array[i].value = value;

                count++;
                return &(array[i].value);
            }
        
        return nullptr;
    }

    template <class T>
    inline bool MemoryPool<T>::deallocate(T* pointer)
    {
        if(isEmpty())
            return false;

        int index = (int)pointer - (int)array.get();
        index /= sizeof(T);

        if(index < 0 || index >= size)
            return false;


        array[index].isFree = true;
        array[index].value = nullValue;
        count--;
        return true;
    }

    template <class T>
    inline bool MemoryPool<T>::isEmpty() const
    {
        return (count == 0);
    }

    template <class T>
    inline bool MemoryPool<T>::isFull() const
    {
        return (count == size);
    }
}
