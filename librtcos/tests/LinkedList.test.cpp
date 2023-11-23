/**
 * @file LinkedList.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/LinkedList.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;

TEST_GROUP(LinkedListTest)
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

TEST(LinkedListTest, newList_isEmpty)
{
    LinkedList list(10);

    CHECK(list.isEmpty());
    CHECK_FALSE(list.isFull());
}

TEST(LinkedListTest, newList_sizeZero_isFullAndEmpty)
{
    LinkedList list(0);

    CHECK(list.isEmpty());
    CHECK(list.isFull());
}

TEST(LinkedListTest, put_isNotEmpty)
{
    LinkedList list(10);

    CHECK(list.put(letterA));

    CHECK_FALSE(list.isEmpty());
    CHECK_FALSE(list.isFull());
}

TEST(LinkedListTest, put_sizeOne_isFull)
{
    LinkedList list(1);

    CHECK(list.put(letterA));

    CHECK(list.isFull());
    CHECK_FALSE(list.put(letterA));
}

TEST(LinkedListTest, put_sizeZero_Failed)
{
    LinkedList list(0);

    CHECK_FALSE(list.put(letterA));
}

TEST(LinkedListTest, get_receivesSameValue)
{
    LinkedList list(10);
    list.put(letterA);

    CHECK_EQUAL(letterA, list.get());
}

TEST(LinkedListTest, remove_isEmpty)
{
    LinkedList list(10);
    list.put(letterA);

    CHECK_FALSE(list.isEmpty());
    list.remove();
    CHECK(list.isEmpty()); 
}

TEST(LinkedListTest, put_thenGet_twoValues)
{
    LinkedList list(10);
    list.put(letterA);

    CHECK_EQUAL(letterA, list.get());
    CHECK(list.put(letterB));
    CHECK_EQUAL(letterA, list.get());
}

TEST(LinkedListTest, put_thenGetAndRemove_twoValues)
{
    LinkedList list(10);
    list.put(letterA);

    CHECK(list.put(letterB));

    CHECK_EQUAL(letterA, list.get());
    list.remove();
    CHECK_EQUAL(letterB, list.get());
    list.remove();
    CHECK_EQUAL(char(), list.get());
}