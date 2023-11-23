#pragma once

namespace rtcos
{
    template <class T>
    inline Buffer<T>::Buffer(size_t size, const T & nullValue)
        : array(nullptr)
        , size(size)
        , count(0)
        , nullValue(nullValue)
    {
        array = new T[size];
        eraseTo(size);
    }

    template <class T>
    inline Buffer<T>::~Buffer()
    {
        delete[] array;
    }

    template <class T>
    inline void Buffer<T>::clear()
    {
        eraseTo(count);
        count = 0;
    }

    template <class T>
    inline bool Buffer<T>::put(const T& value)
    {
        if(isFull())
            return false;

        array[count++] = value;
        return true;
    }

    template <class T>
    inline bool Buffer<T>::isFull() const
    {
        return (count == size);
    }

    template <class T>
    inline bool Buffer<T>::isEmpty() const
    {
        return (count == 0);
    }

    template <class T>
    inline void Buffer<T>::eraseTo(size_t to)
    {
        for(auto i = 0U; i < to; i++)
            array[i] = nullValue;
    }
}
