#include "Clock.hpp"

using namespace rtcos;

Clock::Clock(size_t size)
    : pool(size, { .observer = nullptr, .tick = 0 })
    , tick(0)
{
}

void Clock::update()
{
    tick++;

    for(auto i = 0; i < pool.getSize(); i++)
    {
        auto& alarm = (Alarm&)pool[i];

        if(alarm.observer != nullptr && 
            alarm.tick <= tick)
        {
            alarm.observer->notify();
            pool.deallocate(&alarm);
        }
    }
}

bool Clock::addAlarm(Observer* newObserver, unsigned long long delay)
{
    if((tick + delay) <= tick)
        return false;
    else
        return pool.allocate({ .observer = newObserver, 
            .tick = (this->tick + delay) });
}
