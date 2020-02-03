#pragma once

#include "spdlog/spdlog.h"

class Logger
{
public:
	std::shared_ptr<spdlog::logger> Log;
	Logger() {}
	Logger(std::string name);

	template<typename T>
	void info(T const& args) {
		Log->info(args);
	}

	template<typename ... T>
	void info(std::string fmt, T const... args) {
		Log->info(fmt, args...);
	}
};

