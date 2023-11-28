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
        struct Configuration
        {
            Task& task;
            Scheduler& scheduler;
            Clock& clock;
            unsigned long long delay;
            int priority = 0;
        };

        TimerTask(const Configuration&);

        void execute() override;
        void notify() override;

    private:
        Task& task;
        Scheduler& scheduler;
        Clock& clock;
        unsigned long long delay;
        int priority;
	};
}
