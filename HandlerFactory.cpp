#include "HandlerFactory.h"

std::unique_ptr<Handler> HandlerFactory::createEnterQuizHandler() const
{
	return std::make_unique<EnterQuizHandler>(std::make_shared<HandlerFactory>(*this));
}
