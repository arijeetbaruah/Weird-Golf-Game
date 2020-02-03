// LogTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../Logger/Logger.h"

int main2()
{
	Logger log("console");

	log.info("hi");

	return 0;
}
