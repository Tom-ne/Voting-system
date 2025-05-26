#include "Survey.h"
#include <stdexcept>

Survey::Survey(Blockchain&& blockchain, unsigned int surveyId, const SurveyMetadata meta) : blockchain(std::move(blockchain)), surveyId(surveyId), meta(meta)
{
}

const SurveyMetadata& Survey::getSurveyMetadata() const
{
	return this->meta;
}

const Blockchain& Survey::getBlockchain() const
{
	return this->blockchain;
}

void Survey::addResponse(std::unique_ptr<Response>& response)
{
	if (!response) {
		throw std::runtime_error("Response cannot be null.");
	}

	this->blockchain.createBlock(response);
}
