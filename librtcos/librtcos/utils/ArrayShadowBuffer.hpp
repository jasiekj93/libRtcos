#pragma once

#include <librtcos/ShadowBuffer.hpp>

namespace rtcos::utils
{
    template <class T>
    class ArrayShadowBuffer : public ShadowBuffer<T>
    {
    public:
        ArrayShadowBuffer(size_t, const T& nullValue = char());

    private:
        Buffer<T> first;
        Buffer<T> second;
    };


    template <class T>
    inline ArrayShadowBuffer<T>::ArrayShadowBuffer(size_t size, const T &nullValue)
        : ShadowBuffer<T>(first, second)
        , first(size, nullValue)
        , second(size, nullValue)
    {
    }
}