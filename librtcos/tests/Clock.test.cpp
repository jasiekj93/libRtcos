/**
 * @file Clock.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-24
 */

#include <librtcos/Clock.hpp>
#include <librtcos/PriorityLinkedList.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;

TEST_GROUP(ClockTest)
{
    class TestObserver : public Clock::Observer
    {
    public:
        TestObserver(std::string& s) : str(s) {}

        void notify()
        {
            str += "T";
        }

    private:
        std::string& str;
    };

    TestObserver* observer;
    std::string* str;

    void setup()
    {
        str = new std::string();
        observer = new TestObserver(*str);
    }

    void teardown()
    {
        delete str;
        delete observer;
    }
};

TEST(ClockTest, addAlarm_zeroSize_failed)
{
    Clock clock(0);

    CHECK_FALSE(clock.addAlarm(observer, 500));
}

TEST(ClockTest, addAlarm_delayTooBig)
{
    Clock clock(10);
    unsigned long long max = -1;
    clock.update();

    CHECK_FALSE(clock.addAlarm(observer, max));
}

TEST(ClockTest, addAlarm_success)
{
    Clock clock(10);
    CHECK(clock.addAlarm(observer, 500));
}

TEST(ClockTest, update_noObsevers)
{
    Clock clock(10);
    clock.update();

    STRCMP_EQUAL("", str->c_str());
}

TEST(ClockTest, update_nothingHappened)
{
    Clock clock(10);
    clock.addAlarm(observer, 2);

    clock.update();

    STRCMP_EQUAL("", str->c_str());
}

TEST(ClockTest, update_observerNotified)
{
    Clock clock(10);
    clock.addAlarm(observer, 2);

    clock.update();
    clock.update();

    STRCMP_EQUAL("T", str->c_str());
}

TEST(ClockTest, update_twoObservers)
{
    Clock clock(10);
    clock.addAlarm(observer, 1);
    clock.addAlarm(observer, 1);

    clock.update();

    STRCMP_EQUAL("TT", str->c_str());
}