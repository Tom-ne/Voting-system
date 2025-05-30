#pragma once
#include <memory>
#include "Handler.h"
#include "EnterQuizHandler.h"

class HandlerFactory
{
public:
	std::unique_ptr<Handler> createEnterQuizHandler() const;
};
