#pragma once

/**
 * @file Task.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/Task.hpp>
#include <librtcos/Scheduler.hpp>

namespace rtcos
{
	class ContinousTask : public Task
	{
	public:
        ContinousTask(Task&, Scheduler&);
        void execute() override;

    private:
        Task& task;
        Scheduler& scheduler;
	};
}
