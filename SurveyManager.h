#pragma once
#include "Survey.h"
#include <vector>

class SurveyManager
{
public:
	SurveyManager();
	~SurveyManager();

	void createSurvey(SurveyMetadata& metadata);
	Survey& getSurvey(unsigned int surveyId);
private:
	std::vector<std::unique_ptr<Survey>> surveys;
};

