#include "FileLogger.h"

#include <iostream>
#include "spdlog/sinks/basic_file_sink.h"

using namespace std;
using namespace spdlog;

FileLogger::FileLogger(string name, string fileLocation) {
	try {
		Log = basic_logger_mt(name, fileLocation);
	}
	catch (const spdlog::spdlog_ex& ex) {
		cerr << "Log init failed: " << ex.what() << endl;
		exit(-1);
	}
	Log->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
	Log->info("Welcome to spdlog! {}", 8);
}

FileLogger::FileLogger(string name) {
	string fileLocation = "logs/log.txt";
	try {
		Log = basic_logger_mt(name, fileLocation);
	}
	catch (const spdlog::spdlog_ex& ex) {
		cerr << "Log init failed: " << ex.what() << endl;
		exit(-1);
	}
	Log->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
	Log->info("Welcome to spdlog! {}", 8);
}
