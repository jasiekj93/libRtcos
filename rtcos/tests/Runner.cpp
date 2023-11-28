/**
 * @file Runner.cpp
 * @author Adrian Szczepanski
 * @date 2023-11-22
 */

#include <CppUTest/CommandLineTestRunner.h>

int main(int argc, char* argv[])
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
