#pragma once
#include <memory>
#include <unordered_map>

class Handler
{
public:
	virtual std::unique_ptr<Handler> handleRequest(std::unordered_map<std::string, std::string> input) const = 0;
	virtual bool isRequestValid(std::unordered_map <std::string, std::string> input) const = 0;
};
