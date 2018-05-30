/**
 * @file main.c
 *   Application entry point
 */
#include <stdio.h>

extern int ucltest(int argc, char** argv);
int main(int argc, char** argv)
{
	return ucltest(argc, argv);
}
