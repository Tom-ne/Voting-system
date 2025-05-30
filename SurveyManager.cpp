#include "SurveyManager.h"
#include "SurveyNotFoundException.h"

SurveyManager::SurveyManager()
{
}

SurveyManager::~SurveyManager()
{
}

void SurveyManager::createSurvey(SurveyMetadata& metadata)
{
	Blockchain blockchain;
	this->surveys.push_back(std::make_unique<Survey>(
		std::move(blockchain),
		this->surveys.size() + 1,
		std::move(metadata)
	));
}

Survey& SurveyManager::getSurvey(unsigned int surveyId)
{
    auto it = std::lower_bound(this->surveys.begin(), this->surveys.end(), surveyId,
        [](const std::unique_ptr<Survey>& s, unsigned int id) {
            return s->getSurveyId() < id;
        });

    if (it != this->surveys.end() && (*it)->getSurveyId() == surveyId) {
        return *(*it); // Dereference unique_ptr to return Survey&
    }
    else {
        throw SurveyNotFoundException("Unable to find survey with id " + std::to_string(surveyId));
    }
}
