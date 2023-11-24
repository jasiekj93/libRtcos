#pragma once

/**
 * @file Task.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/Task.hpp>
#include <librtcos/Clock.hpp>

namespace rtcos
{
	class TimerTask 
        : public Task
        , public Clock::Observer
	{
	public:
        TimerTask(unsigned long long delay,
            Task&, Clock&, Scheduler&);

        void execute() override;
        void notify() override;

    private:
        Task& task;
        Scheduler& scheduler;
        Clock& clock;
        unsigned long long delay;
	};
}
