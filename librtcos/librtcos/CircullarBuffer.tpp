#pragma once

namespace rtcos
{
    template <class T>
	inline CircullarBuffer<T>::CircullarBuffer(size_t size)
		: size(size)
		, count(0)
		, putIndex(0)
		, getIndex(0)
		, array(nullptr)
	{
		array = new T[size];

		for(auto i = 0U; i < size; i++)
			array[i] = T();
	}

    template <class T>
    inline CircullarBuffer<T>::~CircullarBuffer()
    {
		delete[] array;
    }

    template <class T>
    inline T CircullarBuffer<T>::get()
    {
        return array[getIndex];
    }

    template <class T>
    inline bool CircullarBuffer<T>::put(T& value)
    {
		if(size == count)
			return false;

		array[putIndex] = value;
		increment(putIndex);
		count++;
		return true;
    }

    template <class T>
    inline void CircullarBuffer<T>::remove()
    {
		if(count == 0)
			return;
		
		array[getIndex] = T();
		increment(getIndex);
		count--;
    }

    template <class T>
    inline bool CircullarBuffer<T>::isEmpty()
    {
        return (count == 0);
    }

    template <class T>
    inline bool CircullarBuffer<T>::isFull()
    {
        return (count == size);
    }

    template <class T>
    inline void CircullarBuffer<T>::increment(size_t& index)
    {
		index = ((index + 1) % size);
    }
}
