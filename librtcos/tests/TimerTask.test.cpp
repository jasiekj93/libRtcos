/**
 * @file TimerTask.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-24
 */

#include <librtcos/TimerTask.hpp>
#include <librtcos/utils/PriorityLinkedList.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;

TEST_GROUP(TimerTaskTest)
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

    std::string* string;
    TestTask* task;
    PriorityQueue<Task*>* queue;
    Scheduler* scheduler;
    Clock* clock;

    void setup()
    {
        string = new std::string();
        task = new TestTask(*string);
        queue = new utils::PriorityLinkedList<Task*>(10);
        scheduler = new Scheduler(*queue);
        clock = new Clock(10);
    }

    void teardown()
    {
        delete clock;
        delete scheduler;
        delete queue;
        delete task;
        delete string;
    }
};

TEST(TimerTaskTest, execute)
{
    static constexpr auto DELAY = 1;
	TimerTask timerTask({ *task, *scheduler, *clock, DELAY });

    scheduler->start();
    STRCMP_EQUAL("", string->c_str());

    clock->update();
    scheduler->start();
    STRCMP_EQUAL("Task", string->c_str());

    scheduler->start();
    STRCMP_EQUAL("Task", string->c_str());

    clock->update();
    scheduler->start();
    STRCMP_EQUAL("TaskTask", string->c_str());
}
