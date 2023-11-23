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
	class BufferTask : public Task
	{
	public:
		BufferTask(ShadowBuffer<char>&);

        void execute() override;

    protected:
        virtual void disableBufferInterrupt() {}
        virtual void enableBufferInterrupt() {}

        virtual void process(const char* data, size_t count) = 0;

    private:
        ShadowBuffer<char>& buffer;
	};

    inline BufferTask::BufferTask(ShadowBuffer<char>& b)
        : buffer(b)
    {
    }

    void BufferTask::execute()
    {
        disableBufferInterrupt();
        buffer.swap();
        enableBufferInterrupt();

        auto& output = buffer.getOutput();
        process(output.getData(), output.getSize());
        output.clear();
    }
}
