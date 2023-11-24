#include "TimerTask.hpp"

using namespace rtcos;

TimerTask::TimerTask(unsigned long long delay, 
    Task& t, 
    Clock& c, 
    Scheduler& s)
    : task(t)
    , scheduler(s)
    , clock(c)
    , delay(delay)
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
    scheduler.addTask(this);
}
