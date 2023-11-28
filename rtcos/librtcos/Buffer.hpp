#pragma once

/**
 * @file Buffer.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <cstddef>

namespace rtcos
{
    template <class T>
	class Buffer
	{
	public:
        virtual ~Buffer() {}

        virtual const T& operator[](int i) const = 0;
        virtual void clear() = 0;
        virtual bool put(const T&) = 0;

        virtual bool isFull() const = 0;
        virtual bool isEmpty() const = 0;

        virtual size_t getSize() const = 0;
        virtual size_t getCount() const = 0;
        virtual const T* getData() const = 0;
	};
}

