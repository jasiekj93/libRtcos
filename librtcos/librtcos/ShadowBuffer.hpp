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
		inline auto& getInput() { return *input; }
		inline auto& getOutput() { return *output; }

		inline void swap() { std::swap(input, output); }

    protected:
        ShadowBuffer(Buffer<T>& in, Buffer<T>& out);

	private:
		Buffer<T>* input;
		Buffer<T>* output;
	};


    template <class T>
    inline ShadowBuffer<T>::ShadowBuffer(Buffer<T>& in, Buffer<T>& out)
        : input(&in)
        , output(&out)
    {
    }
}