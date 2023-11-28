#include "TimerTask.hpp"

using namespace rtcos;

TimerTask::TimerTask(const Configuration& config)
    : task(config.task)
    , scheduler(config.scheduler)
    , clock(config.clock)
    , delay(config.delay)
    , priority(config.priority)
{
    clock.addAlarm(this, delay);
}

void TimerTask::execute()
{
    task.execute();
    clock.addAlarm(this, delay);
}

void TimerTask::notify()
{
    scheduler.addTask(this, priority);
}
