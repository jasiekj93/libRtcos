#pragma once

/**
 * @file BufferTask.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/Task.hpp>
#include <librtcos/Buffer.hpp>

namespace rtcos
{
	class BufferTask : public Task
	{
	public:
		BufferTask(Buffer<char>&);

        void execute() override;

    protected:
        virtual void disableBufferInterrupt() {}
        virtual void enableBufferInterrupt() {}

        virtual void process(const char* data, size_t count) = 0;

    private:
        Buffer<char>& inputBuffer;
        Buffer<char> taskBuffer;
	};

    inline BufferTask::BufferTask(Buffer<char>& b)
        : inputBuffer(b)
        , taskBuffer(b.clone())
    {
    }

    void BufferTask::execute()
    {
        disableBufferInterrupt();
        inputBuffer.dropTo(taskBuffer);
        enableBufferInterrupt();

        process(taskBuffer.getData(), taskBuffer.getSize());
        taskBuffer.clear();
    }
}
