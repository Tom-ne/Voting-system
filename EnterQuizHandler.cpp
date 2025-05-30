#include "EnterQuizHandler.h"
#include "HandlerFactory.h"
#include <iostream>

EnterQuizHandler::EnterQuizHandler(std::shared_ptr<HandlerFactory> handleFactory) : handlerFactory(std::move(handleFactory))
{
}

std::unique_ptr<Handler> EnterQuizHandler::handleRequest(std::unordered_map<std::string, std::string> input) const
{
	return handlerFactory->createEnterQuizHandler();
}

bool EnterQuizHandler::isRequestValid(std::unordered_map<std::string, std::string> input) const
{
	return false;
}
