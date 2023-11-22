/**
 * @file CircullarBuffer.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-22
 */

#include <librtcos/CircullarBuffer.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;

TEST_GROUP(CircullarBufferTest)
{
	void setup()
	{

	}

	void teardown()
	{
		
	}
};

TEST(CircullarBufferTest, get_emptyList_returnNull)
{
	CircullarBuffer<int> buffer(10);
	CHECK(buffer.isEmpty());
	CHECK_EQUAL(int(), buffer.get());
}

TEST(CircullarBufferTest, put_zeroSize_returnFalse)
{
	int value = 5;
	CircullarBuffer<int> buffer(0);

	CHECK_FALSE(buffer.put(value));

	CHECK(buffer.isEmpty());
}

TEST(CircullarBufferTest, put_notEmpty_getReturnsEqual)
{
	int value = 5;
	CircullarBuffer<int> buffer(10);

	CHECK(buffer.put(value));

	CHECK_FALSE(buffer.isEmpty());
	CHECK_EQUAL(value, buffer.get());
}

TEST(CircullarBufferTest, removeAfterPut)
{
	int value = 5;
	CircullarBuffer<int> buffer(10);

	buffer.put(value);
	buffer.remove();

	CHECK(buffer.isEmpty());
	CHECK_EQUAL(int(), buffer.get());
}

TEST(CircullarBufferTest, put_two_butSizeIsOne)
{
	int first = 5;
	int second = 6;
	CircullarBuffer<int> buffer(1);

	CHECK(buffer.put(first));
	CHECK_FALSE(buffer.put(second));

	CHECK_EQUAL(first, buffer.get());
	CHECK(buffer.isFull());
}

TEST(CircullarBufferTest, putTwo_remove_getSecond)
{
	int first = 5;
	int second = 6;
	CircullarBuffer<int> buffer(10);

	buffer.put(first);
	CHECK(buffer.put(second));

	buffer.remove();

	CHECK_EQUAL(second, buffer.get());
}

TEST(CircullarBufferTest, removeAll_isEmpty)
{
	int first = 5;
	int second = 6;
	CircullarBuffer<int> buffer(10);

	buffer.put(first);
	buffer.put(second);

	buffer.remove();
	buffer.remove();

	CHECK(buffer.isEmpty());
}