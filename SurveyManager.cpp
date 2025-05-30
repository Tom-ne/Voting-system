#include "SurveyManager.h"
#include "SurveyNotFoundException.h"

SurveyManager::SurveyManager()
{
}

SurveyManager::~SurveyManager()
{
}

void SurveyManager::createSurvey(Survey& survey)
{
	survey.setSurveyId(surveys.size() + 1);
	this->surveys.push_back(survey);
}

Survey& SurveyManager::getSurvey(unsigned int surveyId)
{
	// because the surveys are sorted by id, we can use binary search
	auto it = std::lower_bound(this->surveys.begin(), this->surveys.end(), surveyId, [](const Survey& s, unsigned int id) {
			return s.getSurveyId() < id;
	});
	if (it != this->surveys.end() && it->getSurveyId() == surveyId) {
		return *it;
	}
	else {
		throw SurveyNotFoundException("Unable to find survey with id " + surveyId);
	}
}
