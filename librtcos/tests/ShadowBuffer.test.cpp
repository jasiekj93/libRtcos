/**
 * @file ShadowBuffer.test.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/ShadowBuffer.hpp>

#include <CppUTest/TestHarness.h>

using namespace rtcos;

TEST_GROUP(ShadowBufferTest)
{
};

TEST(ShadowBufferTest, swap)
{
	ShadowBuffer<char> buffer(10);
	buffer.getInput().put('a');
	buffer.getOutput().put('b');

	buffer.swap();

	CHECK_EQUAL('b', buffer.getInput()[0]);
	CHECK_EQUAL('a', buffer.getOutput()[0]);
}
