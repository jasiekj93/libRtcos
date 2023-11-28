/**
 * @file ArrayBuffer.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/utils/ArrayBuffer.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;
using namespace rtcos::utils;

TEST_GROUP(ArrayBufferTest)
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

TEST(ArrayBufferTest, newBuffer_isEmpty)
{
    constexpr auto SIZE = 10U;
	ArrayBuffer<char> buffer(SIZE);

    CHECK(buffer.isEmpty());
    CHECK_FALSE(buffer.isFull());
}

TEST(ArrayBufferTest, newBuffer_isErased)
{
    constexpr auto SIZE = 10U;
	ArrayBuffer<char> buffer(SIZE);

    for(auto i = 0U; i < SIZE; i++)
        CHECK_EQUAL(char(), buffer[i]);
}

TEST(ArrayBufferTest, put_oneValue)
{
	ArrayBuffer<char> buffer(10);

    CHECK(buffer.put(letterA));
    CHECK_EQUAL(letterA, buffer[0]);
    CHECK_EQUAL(1, buffer.getCount());
}

TEST(ArrayBufferTest, put_zeroSize_isFull)
{
	ArrayBuffer<char> buffer(0);

    CHECK_FALSE(buffer.put(letterA));
    CHECK(buffer.isFull());
}

TEST(ArrayBufferTest, clear_isEmpty_andValueErased)
{
	ArrayBuffer<char> buffer(10);
    buffer.put(letterA);
    CHECK_EQUAL(letterA, buffer[0]);

    buffer.clear();

    CHECK(buffer.isEmpty());
    CHECK_EQUAL(char(), buffer[0]);
}

TEST(ArrayBufferTest, dropTo_secondIsTooSmall)
{
	ArrayBuffer<char> first(10);
	ArrayBuffer<char> second(1);
    first.put(letterA);
    first.put(letterA);

    CHECK_FALSE(first.dropTo(second));
    CHECK_FALSE(first.isEmpty());
}

TEST(ArrayBufferTest, dropTo_OneValue)
{
	ArrayBuffer<char> first(10);
	ArrayBuffer<char> second(1);
    first.put(letterA);

    CHECK(first.dropTo(second));

    CHECK_EQUAL(1, second.getCount());
    CHECK_EQUAL(letterA, second[0]);
}

TEST(ArrayBufferTest, dropTo_firstWasCleared)
{
	ArrayBuffer<char> first(10);
	ArrayBuffer<char> second(1);
    first.put(letterA);

    first.dropTo(second);

    CHECK(first.isEmpty());
    CHECK_EQUAL(char(), first[0]);
}

TEST(ArrayBufferTest, dropTo_secondWasCleared)
{
	ArrayBuffer<char> first(10);
	ArrayBuffer<char> second(10);
    first.put(letterA);
    second.put(letterB);
    second.put(letterB);

    first.dropTo(second);

    CHECK_EQUAL(1, second.getCount());
    CHECK_EQUAL(letterA, second[0]);
    CHECK_EQUAL(char(), second[1]);
}