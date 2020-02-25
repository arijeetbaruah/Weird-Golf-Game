#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

//@Author: Arijeet Baruah
class Logger
{
protected:
	std::shared_ptr<spdlog::logger> logger;
public:
	Logger() {
	}

	Logger(std::string name) {
		logger = spdlog::stdout_color_mt(name + " console");
		logger->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
	}

	template<typename T>
	void info(T const& args) {
		logger->info(args);
	}

	template<typename ... T>
	void info(std::string fmt, T const... args) {
		logger->info(fmt, args...);
	}

	template<typename T>
	void error(T const& args) {
		logger->error(args);
	}

	template<typename ... T>
	void error(std::string fmt, T const... args) {
		logger->error(fmt, args...);
	}

	template<typename T>
	void critical(T const& args) {
		logger->critical(args);
	}

	template<typename ... T>
	void critical(std::string fmt, T const... args) {
		logger->critical(fmt, args...);
	}

	template<typename T>
	void debug(T const& args) {
		logger->debug(args);
	}

	template<typename ... T>
	void debug(std::string fmt, T const... args) {
		logger->debug(fmt, args...);
	}
};

