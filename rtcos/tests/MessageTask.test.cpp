/**
 * @file MessageTask.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/MessageTask.hpp>
#include <librtcos/utils/CircullarBuffer.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;

TEST_GROUP(MessageTaskTest)
{
    class TestMessageTask : public MessageTask<char>
    {
    public:
		TestMessageTask(Queue<char>& q, std::string& s)
            : MessageTask(q)
            , str(s)
        {}

    protected:
        virtual void disableQueueInterrupt() { str += "Disabled "; };
        virtual void enableQueueInterrupt() { str += "Enabled "; };

        void process(char& message) override
        {
            str += "Processing:";
            str += message; 
        }

    private:
        std::string& str;
    };
};

TEST(MessageTaskTest, process)
{
    std::string str;
    utils::CircullarBuffer<char> queue(10);
    TestMessageTask task(queue, str);

    queue.put('u');
    task.execute();

    STRCMP_EQUAL("Disabled Enabled Processing:u", str.c_str());
}
