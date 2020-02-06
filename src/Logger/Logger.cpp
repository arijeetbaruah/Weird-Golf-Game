#include "./Logger/Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace std;
using namespace spdlog;

Logger::Logger(string name) {
	Log = stdout_color_mt(name);
	Log->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
	Log->info("Welcome to spdlog! {}", 8);
}

Logger* Logger::get(std::string name) {
	return new Logger (spdlog::get(name));
}
