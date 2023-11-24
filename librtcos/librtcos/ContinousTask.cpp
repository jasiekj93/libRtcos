#include "ContinousTask.hpp"

using namespace rtcos;

ContinousTask::ContinousTask(Task& t, Scheduler& s)
    : task(t)
    , scheduler(s)
{
}

void ContinousTask::execute()
{
    task.execute();
    scheduler.addTask(this);
}
