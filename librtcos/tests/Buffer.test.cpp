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
    char letterB = 'b';

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

TEST(BufferTest, dropTo_secondIsTooSmall)
{
	Buffer<char> first(10);
	Buffer<char> second(1);
    first.put(letterA);
    first.put(letterA);

    CHECK_FALSE(first.dropTo(second));
    CHECK_FALSE(first.isEmpty());
}

TEST(BufferTest, dropTo_OneValue)
{
	Buffer<char> first(10);
	Buffer<char> second(1);
    first.put(letterA);

    CHECK(first.dropTo(second));

    CHECK_EQUAL(1, second.getCount());
    CHECK_EQUAL(letterA, second[0]);
}

TEST(BufferTest, dropTo_firstWasCleared)
{
	Buffer<char> first(10);
	Buffer<char> second(1);
    first.put(letterA);

    first.dropTo(second);

    CHECK(first.isEmpty());
    CHECK_EQUAL(char(), first[0]);
}

TEST(BufferTest, dropTo_secondWasCleared)
{
	Buffer<char> first(10);
	Buffer<char> second(10);
    first.put(letterA);
    second.put(letterB);
    second.put(letterB);

    first.dropTo(second);

    CHECK_EQUAL(1, second.getCount());
    CHECK_EQUAL(letterA, second[0]);
    CHECK_EQUAL(char(), second[1]);
}