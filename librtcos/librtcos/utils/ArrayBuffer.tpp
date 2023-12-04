#pragma once

namespace rtcos::utils
{
    template <class T>
    inline ArrayBuffer<T>::ArrayBuffer(size_t s, const T & nullValue)
        : array(std::make_unique<T[]>(s))
        , size(s)
        , count(0)
        , nullValue(nullValue)
    {
        eraseTo(size);
    }

    template <class T>
    inline void ArrayBuffer<T>::clear()
    {
        eraseTo(count);
        count = 0;
    }

    template <class T>
    inline bool ArrayBuffer<T>::put(const T& value)
    {
        if(isFull())
            return false;

        array[count++] = value;
        return true;
    }

    template<class T>
    bool ArrayBuffer<T>::dropTo(ArrayBuffer& buffer)
    {
        if(count > buffer.size)
            return false;

        buffer.clear();
        std::copy(begin(), end(), buffer.begin());
        buffer.count = count;

        clear(); 
        return true;
    }

    template <class T>
    inline bool ArrayBuffer<T>::isFull() const
    {
        return (count == size);
    }

    template <class T>
    inline bool ArrayBuffer<T>::isEmpty() const
    {
        return (count == 0);
    }

    template <class T>
    inline ArrayBuffer<T> ArrayBuffer<T>::clone() const
    {
        return ArrayBuffer(this->size, this->nullValue);
    }

    template <class T>
    inline void ArrayBuffer<T>::eraseTo(size_t to)
    {
        for(auto i = 0U; i < to; i++)
            array[i] = nullValue;
    }
}
