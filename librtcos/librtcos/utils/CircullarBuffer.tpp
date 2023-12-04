#pragma once

namespace rtcos::utils
{
    template <class T>
	inline CircullarBuffer<T>::CircullarBuffer(size_t s, const T& nullValue)
		: size(s)
		, count(0)
		, putIndex(0)
		, getIndex(0)
		, array(std::make_unique<T[]>(s))
        , nullValue(nullValue)
	{
		for(auto i = 0U; i < size; i++)
			array[i] = nullValue;
	}

    template <class T>
    inline T CircullarBuffer<T>::get() const
    {
        return array[getIndex];
    }

    template <class T>
    inline bool CircullarBuffer<T>::put(const T& value)
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
		
		array[getIndex] = nullValue;
		increment(getIndex);
		count--;
    }

    template <class T>
    inline bool CircullarBuffer<T>::isEmpty() const 
    {
        return (count == 0);
    }

    template <class T>
    inline bool CircullarBuffer<T>::isFull() const
    {
        return (count == size);
    }

    template <class T>
    inline void CircullarBuffer<T>::increment(size_t& index)
    {
		index = ((index + 1) % size);
    }
}
