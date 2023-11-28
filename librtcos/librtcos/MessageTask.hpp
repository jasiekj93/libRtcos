#pragma once

/**
 * @file Task.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/Task.hpp>
#include <librtcos/Queue.hpp>

namespace rtcos
{
    template <class T>
	class MessageTask : public Task
	{
	public:
        MessageTask(Queue<T>&, const T& initial = T());

        void execute() override;

    protected:
        virtual void disableQueueInterrupt() {}
        virtual void enableQueueInterrupt() {}

        virtual void process(T& message) = 0;

    private:
        Queue<T>& queue;
        T message;
	};

}

#include <librtcos/MessageTask.tpp>