#pragma once
#include "Survey.h"
#include <vector>

class SurveyManager
{
public:
	SurveyManager();
	~SurveyManager();

	void createSurvey(Survey& survey);
	Survey& getSurvey(unsigned int surveyId);
private:
	std::vector<Survey> surveys;
};

