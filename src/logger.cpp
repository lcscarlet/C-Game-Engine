#include "logger.h"
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>


std::vector<LogEntry> Logger::messages;

//Do I really need both ctime and chrono?
//SPDLog library (potential replacement): https://github.com/gabime/spdlog



//----------------------------------------------------------------
// This logger uses CurrentDateTimeToString to create a log in either
//green or red text depending on if it's a log or an error. The log ,is also prefixed with the current date and time. I might want to change this later to write to a file instead of the console, but for now this is good enough for debugging purposes.
// 
// strftime() formats time as string, with specifiers. 
//----------------------------------------------------------------


std::string CurrentDateTimeToString() {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string output(30, '\0');
	std::strftime(&output[0], output.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	return output;
}

//----------------------------------------------------------------
//\x1B[32m is the ANSI escape code for green text, and \033[0m resets the text color to default. Similarly, \x1B[31m is the ANSI escape code for red text. 
//----------------------------------------------------------------

void Logger::Log(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = LOG_INFO;
	logEntry.message = "LOG: [" + CurrentDateTimeToString() + "] " + message;
	std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << std::endl; 

	messages.push_back(logEntry);
};

void Logger::Err(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = LOG_ERROR;
	logEntry.message = "ERR: [" + CurrentDateTimeToString() + "] " + message;
	std::cerr << "\x1B[31m" << logEntry.message << "\033[0m" << std::endl;
};