/**
 * @file ucltestTest.cpp
 *   This is a test for ucltest main function.
 */
#include <CppUTest/TestHarness.h>

extern "C" int ucltest(int argc, char** argv);

TEST_GROUP(ucltest)
{
};

TEST(ucltest, case1)
{
	/* TODO: Write main test. */
	char* dummy[] = {(char*)"dummy"};
	LONGS_EQUAL(0, ucltest(1, (char**)dummy));
}

