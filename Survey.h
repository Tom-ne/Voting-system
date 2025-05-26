#pragma once
#include "SurveyMetadata.h"
#include "Blockchain.h"

class Survey
{
public:
	Survey(Blockchain&& blockchain, unsigned int surveyId, const SurveyMetadata meta);

	const SurveyMetadata& getSurveyMetadata() const;
	const Blockchain& getBlockchain() const;

	void addResponse(std::unique_ptr<Response>& response);

private:
	SurveyMetadata meta;
	Blockchain blockchain;
	unsigned int surveyId;
};

