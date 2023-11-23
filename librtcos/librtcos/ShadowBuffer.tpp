#pragma once

namespace rtcos
{
	template <class T>
	inline ShadowBuffer<T>::ShadowBuffer(size_t size, const T& nullValue)
		: first(size, nullValue)
		, second(size, nullValue)
		, input(&first)
		, output(&second)
	{
	}

	template <class T>
    inline void ShadowBuffer<T>::swap()
    {
		std::swap(input, output);
    }
}
