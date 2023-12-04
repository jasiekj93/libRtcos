#pragma once

/**
 * @file MemoryPool.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-24
 */

#include <cstddef>
#include <memory>

namespace rtcos::utils
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

        T* allocate(const T&);
        bool deallocate(T*);

        inline const auto& operator[](int i) const { return array[i].value; }

        bool isEmpty() const;
        bool isFull() const;

        inline auto getData() const { return array.get(); }
        inline auto getSize() const { return size; }
        inline auto getCount() const { return count; }
        inline auto getNullValue() const { return nullValue; }

        inline auto begin() { return array.get(); }
        inline auto begin() const { return array.get(); }
        inline auto end() { return array.get() + size; }
        inline auto end() const { return array.get() + size; }

    private:
        size_t size;
        size_t count;
        std::unique_ptr<Segment[]> array;
        T nullValue;
	};
}

#include <librtcos/utils/MemoryPool.tpp>