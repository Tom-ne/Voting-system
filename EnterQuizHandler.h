#pragma once
#include "Handler.h"

class HandlerFactory;

class EnterQuizHandler : public Handler
{
public:
	EnterQuizHandler(std::shared_ptr<HandlerFactory> handleFactory);
	std::unique_ptr<Handler> handleRequest(std::unordered_map<std::string, std::string> input) const override;
	bool isRequestValid(std::unordered_map<std::string, std::string> input) const override;
private:
	std::shared_ptr<HandlerFactory> handlerFactory;
};
