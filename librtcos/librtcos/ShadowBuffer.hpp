#pragma once

/**
 * @file ShadowBuffer.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/Buffer.hpp>
#include <algorithm>

namespace rtcos
{
	template <class T>
	class ShadowBuffer
	{
	public:
		ShadowBuffer(size_t, const T& nullValue = char());

		inline auto& getInput() { return *input; }
		inline auto& getOutput() { return *output; }

		void swap();

	private:
		Buffer<T> first;
		Buffer<T> second;
		Buffer<T>* input;
		Buffer<T>* output;
	};
}

#include <librtcos/ShadowBuffer.tpp>
