#pragma once
#include "Logger.h"

#include <iostream>
#include "spdlog/sinks/basic_file_sink.h"

//@Author: Arijeet Baruah
class fileLogger : public Logger
{
public:
	fileLogger(std::string name, std::string fileLocation) {
		try {
			logger = spdlog::basic_logger_mt(name, fileLocation);
		}
		catch (const spdlog::spdlog_ex& ex) {
			std::cerr << "Log init failed: " << ex.what() << std::endl;
			exit(-1);
		}
		logger->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
	}

	fileLogger(std::string name) {
		std::string fileLocation = "logs/log.txt";
		try {
			logger = spdlog::basic_logger_mt(name, fileLocation);
		}
		catch (const spdlog::spdlog_ex& ex) {
			std::cerr << "Log init failed: " << ex.what() << std::endl;
			exit(-1);
		}
		logger->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
	}
};

