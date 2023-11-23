#include "Scheduler.hpp"

using namespace rtcos;

Scheduler::Scheduler(PriorityQueue<Task*>& q)
    : queue(q)
{
}

void rtcos::Scheduler::start()
{
    isRunning = true;

    while(queue.isEmpty() == false &&
        isRunning)
    {
        disableInterrupts();
        auto task = queue.get();
        queue.remove();
        enableInterrupts();

        task->execute();
    }

    isRunning = false;
}
