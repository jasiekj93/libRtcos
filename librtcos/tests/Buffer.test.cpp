/**
 * @file Buffer.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/Buffer.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;

TEST_GROUP(BufferTest)
{
    char letterA = 'a';

	void setup()
	{

	}

	void teardown()
	{
		
	}
};

TEST(BufferTest, newBuffer_isEmpty)
{
    constexpr auto SIZE = 10U;
	Buffer<char> buffer(SIZE);

    CHECK(buffer.isEmpty());
    CHECK_FALSE(buffer.isFull());
}

TEST(BufferTest, newBuffer_isErased)
{
    constexpr auto SIZE = 10U;
	Buffer<char> buffer(SIZE);

    for(auto i = 0U; i < SIZE; i++)
        CHECK_EQUAL(char(), buffer[i]);
}

TEST(BufferTest, put_oneValue)
{
	Buffer<char> buffer(10);

    CHECK(buffer.put(letterA));
    CHECK_EQUAL(letterA, buffer[0]);
    CHECK_EQUAL(1, buffer.getCount());
}

TEST(BufferTest, put_zeroSize_isFull)
{
	Buffer<char> buffer(0);

    CHECK_FALSE(buffer.put(letterA));
    CHECK(buffer.isFull());
}

TEST(BufferTest, clear_isEmpty_andValueErased)
{
	Buffer<char> buffer(10);
    buffer.put(letterA);
    CHECK_EQUAL(letterA, buffer[0]);

    buffer.clear();

    CHECK(buffer.isEmpty());
    CHECK_EQUAL(char(), buffer[0]);
}