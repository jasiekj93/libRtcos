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
		Buffer(size_t, const T& nullValue = T());
        ~Buffer();

        inline const T& operator[](int i) const { return array[i]; }
        void clear();
        bool put(const T&);

        bool isFull() const;
        bool isEmpty() const;

        inline auto getCount() const { return count; }

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
