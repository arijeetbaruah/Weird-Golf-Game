#pragma once

#include "spdlog/spdlog.h"

class Logger
{
protected:
	std::shared_ptr<spdlog::logger> Log;
public:
	Logger() {}
	Logger(std::shared_ptr<spdlog::logger> Log) {}
	Logger(std::string name);

	template<typename T>
	void info(T const& args) {
		Log->info(args);
	}

	template<typename ... T>
	void info(std::string fmt, T const... args) {
		Log->info(fmt, args...);
	}

	template<typename T>
	void error(T const& args) {
		Log->error(args);
	}

	template<typename ... T>
	void error(std::string fmt, T const... args) {
		Log->error(fmt, args...);
	}

	template<typename T>
	void critical(T const& args) {
		Log->critical(args);
	}

	template<typename ... T>
	void critical(std::string fmt, T const... args) {
		Log->critical(fmt, args...);
	}

	template<typename T>
	void debug(T const& args) {
		Log->debug(args);
	}

	template<typename ... T>
	void debug(std::string fmt, T const... args) {
		Log->debug(fmt, args...);
	}

	static Logger* get(std::string name);
};

