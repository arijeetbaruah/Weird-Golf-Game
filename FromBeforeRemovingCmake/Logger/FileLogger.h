#pragma once
#include "Logger.h"

class FileLogger : public Logger
{
public:
	FileLogger(std::string name);
	FileLogger(std::string name, std::string fileLocation);
};

