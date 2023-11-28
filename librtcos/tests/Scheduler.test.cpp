/**
 * @file Scheduler.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/Scheduler.hpp>
#include <librtcos/utils/PriorityLinkedList.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;

TEST_GROUP(SchedulerTest)
{
	class TestTask : public Task
    {
    public:
        TestTask(std::string& s) : str(s) {}

        void execute()
        {
            str += "Task";

            if(scheduler)
                scheduler->stop();
        }

        Scheduler* scheduler = nullptr;

    private:
        std::string& str;
    };

    class TestScheduler : public Scheduler
    {
    public:
		TestScheduler(PriorityQueue<Task*>& pq, std::string& s)
            : Scheduler(pq)
            , str(s)
        {}

    protected:
        virtual void disableInterrupts() { str += "Disabled "; };
        virtual void enableInterrupts() { str += "Enabled "; };

    private:
        std::string& str;
    };
};

TEST(SchedulerTest, start_oneTask)
{
    std::string string;
    utils::PriorityLinkedList<Task*> queue(10);
	TestScheduler scheduler(queue, string);
    TestTask task(string);
    scheduler.addTask(&task);

    scheduler.start();

    STRCMP_EQUAL("Disabled Enabled Task", string.c_str());
}

TEST(SchedulerTest, start_twoTasks)
{
    std::string string;
    utils::PriorityLinkedList<Task*> queue(10);
	TestScheduler scheduler(queue, string);
    TestTask task(string);
    scheduler.addTask(&task);
    scheduler.addTask(&task);

    scheduler.start();

    STRCMP_EQUAL("Disabled Enabled TaskDisabled Enabled Task", string.c_str());
}

TEST(SchedulerTest, start_twoTasks_withPause)
{
    std::string string;
    utils::PriorityLinkedList<Task*> queue(10);
	TestScheduler scheduler(queue, string);
    TestTask task(string);
    scheduler.addTask(&task);
    scheduler.addTask(&task);
    task.scheduler = &scheduler;

    scheduler.start();

    STRCMP_EQUAL("Disabled Enabled Task", string.c_str());
}