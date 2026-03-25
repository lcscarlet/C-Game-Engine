#include "logger.h"
#include <iostream>
#include <ctime>

void Logger::Log(const std::string& message) {
	struct time t = {0};

	std::printf("LOG: ")
	//display in green
}

void Logger::Err(const std::string& message) {
	std::printf("ERR: ")
	//display in red
}