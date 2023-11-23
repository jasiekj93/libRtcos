#pragma once

/**
 * @file Buffer.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <cstddef>
#include <algorithm>

namespace rtcos
{
    template <class T>
	class Buffer
	{
	public:
		Buffer(size_t, const T& nullValue = T());
        ~Buffer();

        inline const T& operator[](int i) const { return array[i]; }
        void clear();
        bool put(const T&);
        bool dropTo(Buffer& to);

        bool isFull() const;
        bool isEmpty() const;

        inline auto getSize() const { return size; }
        inline auto getCount() const { return count; }
        inline auto getData() const { return array; }

        Buffer clone() const;

    protected:
        void eraseTo(size_t to);

    private:
        T* array;
        const size_t size;
        size_t count;
        const T nullValue;

        Buffer(const Buffer&) = delete;
        Buffer(const Buffer&&) = delete;
        Buffer& operator=(const Buffer&) = delete;
        Buffer& operator=(const Buffer&&) = delete;
	};
}

#include <librtcos/Buffer.tpp>
