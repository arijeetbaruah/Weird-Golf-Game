// LogTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../Logger/Logger.h"

int main()
{
	Logger log("console");
	
	log.info("hi");
	log.info("test {}", 23);
}
