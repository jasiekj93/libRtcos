#pragma once

/**
 * @file Scheduler.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/PriorityQueue.hpp>
#include <librtcos/Task.hpp>

namespace rtcos
{
	class Scheduler
	{
	public:
		Scheduler(PriorityQueue<Task*>&);

        void start();
        
        inline void stop() { isRunning = false; }
        inline bool addTask(Task* t) { return queue.put(t); }

    protected:
        virtual void disableInterrupts() {};
        virtual void enableInterrupts() {};

    private:
        PriorityQueue<Task*>& queue;
        bool isRunning;
	};
}
