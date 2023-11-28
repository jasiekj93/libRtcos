/**
 * @file MemoryPool.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-24
 */

#include <librtcos/utils/MemoryPool.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;
using namespace rtcos::utils;

TEST_GROUP(MemoryPoolTest)
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

TEST(MemoryPoolTest, new_isEmpty)
{
	MemoryPool<char> pool(10);

    CHECK(pool.isEmpty());
    CHECK_FALSE(pool.isFull());
    CHECK_EQUAL(0, pool.getCount());
    CHECK_EQUAL(10, pool.getSize());
}

TEST(MemoryPoolTest, allocate_zeroSize_failed)
{
	MemoryPool<char> pool(0);

    CHECK_FALSE(pool.allocate(letterA));
}

TEST(MemoryPoolTest, allocate_oneValue)
{
	MemoryPool<char> pool(10);

    auto pointer = pool.allocate(letterA);

    CHECK(pointer);
    CHECK_EQUAL(letterA, pool[0]);
}

TEST(MemoryPoolTest, allocate_twoValues)
{
	MemoryPool<char> pool(10);

    pool.allocate(letterA);
    auto pointer = pool.allocate(letterB);

    CHECK(pointer);
    CHECK_EQUAL(letterA, pool[0]);
    CHECK_EQUAL(letterB, pool[1]);
}

TEST(MemoryPoolTest, deallocate_isEmpty)
{
	MemoryPool<char> pool(10);

    auto pointer = pool.allocate(letterA);

    CHECK(pool.deallocate(pointer));

    CHECK_EQUAL(char(), pool[0]);
    CHECK(pool.isEmpty());
}

TEST(MemoryPoolTest, deallocate_emptyPool)
{
	MemoryPool<char> pool(10);

    auto pointer = pool.allocate(letterA);
    pool.deallocate(pointer);

    CHECK_FALSE(pool.deallocate(pointer));
}

TEST(MemoryPoolTest, deallocate_pointerNotFromPool)
{
	MemoryPool<char> pool(10);

    pool.allocate(letterA);

    char local = 'l';

    CHECK_FALSE(pool.deallocate(&local));
}