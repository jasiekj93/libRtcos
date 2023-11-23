/**
 * @file PriorityLinkedList.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/PriorityLinkedList.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;

TEST_GROUP(PriorityLinkedListTest)
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

TEST(PriorityLinkedListTest, newList_isEmpty)
{
    PriorityLinkedList<char> list(10);

    CHECK(list.isEmpty());
    CHECK_FALSE(list.isFull());
}

TEST(PriorityLinkedListTest, newList_sizeZero_isFullAndEmpty)
{
    PriorityLinkedList<char> list(0);

    CHECK(list.isEmpty());
    CHECK(list.isFull());
}

TEST(PriorityLinkedListTest, put_isNotEmpty)
{
    PriorityLinkedList<char> list(10);

    CHECK(list.put(letterA));

    CHECK_FALSE(list.isEmpty());
    CHECK_FALSE(list.isFull());
}

TEST(PriorityLinkedListTest, put_sizeOne_isFull)
{
    PriorityLinkedList<char> list(1);

    CHECK(list.put(letterA));

    CHECK(list.isFull());
    CHECK_FALSE(list.put(letterA));
}

TEST(PriorityLinkedListTest, put_sizeZero_Failed)
{
    PriorityLinkedList<char> list(0);

    CHECK_FALSE(list.put(letterA));
}

TEST(PriorityLinkedListTest, get_receivesSameValue)
{
    PriorityLinkedList<char> list(10);
    list.put(letterA);

    CHECK_EQUAL(letterA, list.get());
}

TEST(PriorityLinkedListTest, remove_isEmpty)
{
    PriorityLinkedList<char> list(10);
    list.put(letterA);

    CHECK_FALSE(list.isEmpty());
    list.remove();
    CHECK(list.isEmpty()); 
}

TEST(PriorityLinkedListTest, put_thenGet_twoValues)
{
    PriorityLinkedList<char> list(10);
    list.put(letterA);

    CHECK_EQUAL(letterA, list.get());
    CHECK(list.put(letterB));
    CHECK_EQUAL(letterA, list.get());
}

TEST(PriorityLinkedListTest, put_thenGetAndRemove_twoValues)
{
    PriorityLinkedList<char> list(10);
    list.put(letterA);

    CHECK(list.put(letterB));

    CHECK_EQUAL(letterA, list.get());
    list.remove();
    CHECK_EQUAL(letterB, list.get());
    list.remove();
    CHECK_EQUAL(char(), list.get());
}

TEST(PriorityLinkedListTest, put_twoValues_OneWithHigherPriority)
{
    PriorityLinkedList<char> list(10);
    list.put(letterA, 0);

    CHECK(list.put(letterB, 1));

    CHECK_EQUAL(letterB, list.get());
}

TEST(PriorityLinkedListTest, workingWithPointers)
{
    PriorityLinkedList<int*> list(10);
    int u = 'u';
    list.put(&u, 0);

    CHECK_EQUAL(&u, list.get());
}