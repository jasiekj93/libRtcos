#pragma once

/**
 * @file MemoryPool.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-24
 */

#include <cstddef>

namespace rtcos
{
    template <class T>
	class MemoryPool
	{
	public:
        struct Segment
        {
            T value;
            bool isFree;
        };

		MemoryPool(size_t, const T& nullValue = T());
        ~MemoryPool();

        T* allocate(const T&);
        bool deallocate(T*);

        inline const auto& operator[](int i) const { return array[i].value; }

        bool isEmpty() const;
        bool isFull() const;

        inline auto getData() const { return array; }
        inline auto getSize() const { return size; }
        inline auto getCount() const { return count; }
        inline auto getNullValue() const { return nullValue; }

    private:
        size_t size;
        size_t count;
        Segment* array;
        T nullValue;

        MemoryPool(const MemoryPool&) = delete;
        MemoryPool(const MemoryPool&&) = delete;
        MemoryPool& operator=(const MemoryPool&) = delete;
        MemoryPool& operator=(const MemoryPool&&) = delete;
	};
}

#include <librtcos/MemoryPool.tpp>
