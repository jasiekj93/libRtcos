#include "Scheduler.hpp"

using namespace rtcos;

Scheduler::Scheduler(PriorityQueue<Task*>& q)
    : queue(q)
{
}

void Scheduler::start()
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

bool Scheduler::addTask(Task *t, int priority)
{
    disableInterrupts();
    auto result = queue.put(t, priority);
    enableInterrupts();

    return result;
}
