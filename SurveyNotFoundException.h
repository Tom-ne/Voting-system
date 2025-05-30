#pragma once
#include <stdexcept>
#include <string>

class SurveyNotFoundException : public std::runtime_error {
public:
	explicit SurveyNotFoundException(const std::string& message)
		: std::runtime_error("Survey Not Found: " + message) {}
	
	explicit SurveyNotFoundException(const char* message)
		: std::runtime_error(std::string("Survey Not Found: ") + message) {}
};