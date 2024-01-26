#pragma once

/**
 * @file BufferTask.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/Task.hpp>
#include <librtcos/ShadowBuffer.hpp>

namespace rtcos
{
    template <class T>
	class BufferTask : public Task
	{
	public:
		BufferTask(ShadowBuffer<T>&);

        void execute() override;

    protected:
        virtual void disableBufferInterrupt() {}
        virtual void enableBufferInterrupt() {}

        virtual void process(const T* data, size_t count) = 0;

    private:
        ShadowBuffer<T>& buffer;
	};
}

#include <librtcos/BufferTask.tpp>