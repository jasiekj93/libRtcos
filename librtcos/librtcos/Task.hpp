#pragma once

/**
 * @file Task.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

namespace rtcos
{
	class Task
	{
	public:
		virtual ~Task() {}

        virtual void execute() = 0;
	};
}
