#pragma once
#include "SurveyMetadata.h"
#include "Blockchain.h"

class Survey
{
public:
	Survey(Blockchain&& blockchain, unsigned int surveyId, const SurveyMetadata meta);

	const SurveyMetadata& getSurveyMetadata() const;
	const Blockchain& getBlockchain() const;

	void addQuestion(const Question& question);

	void addResponse(std::unique_ptr<Response> response);

	void setSurveyId(unsigned int id);
	const unsigned int& getSurveyId() const;

private:
	SurveyMetadata meta;
	Blockchain blockchain;
	unsigned int surveyId;
};

