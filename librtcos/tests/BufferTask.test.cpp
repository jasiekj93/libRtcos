/**
 * @file BufferTask.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/BufferTask.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;

TEST_GROUP(BufferTaskTest)
{
	class TestBufferTask : public BufferTask<char>
    {
    public:
		TestBufferTask(ShadowBuffer<char>& b, std::string& s)
            : BufferTask(b)
            , str(s)
        {}

    protected:
        virtual void disableBufferInterrupt() { str += "Disabled "; };
        virtual void enableBufferInterrupt() { str += "Enabled "; };

        void process(const char* data, size_t count) override
        {
            str += "Processing:";

            for(auto i = 0U; i < count; i++)
                str += data[i]; 
        }

    private:
        std::string& str;
    };
};

TEST(BufferTaskTest, execute)
{
	std::string str;
    ShadowBuffer<char> buffer(10);
    TestBufferTask task(buffer, str);

    buffer.getInput().put('a');
    buffer.getInput().put('b');
    task.execute();

    STRCMP_EQUAL("Disabled Enabled Processing:ab", str.c_str());
    CHECK(buffer.getOutput().isEmpty());
    CHECK(buffer.getInput().isEmpty());
}
