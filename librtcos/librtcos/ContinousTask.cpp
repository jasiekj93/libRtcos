#include "ContinousTask.hpp"

using namespace rtcos;

ContinousTask::ContinousTask(Task& t, Scheduler& s, int priority)
    : task(t)
    , scheduler(s)
    , priority(priority)
{
}

void ContinousTask::execute()
{
    task.execute();
    scheduler.addTask(this, priority);
}
