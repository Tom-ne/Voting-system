#pragma once
#include "SurveyManager.h"
#include "Communicator.h"
#include "HandlerFactory.h"

class Server
{
public:
	Server();
	~Server();

	void run();
private:
	SurveyManager surveyManager;
	std::unique_ptr<Communicator> communicator;
	HandlerFactory handlerFactory;
};

