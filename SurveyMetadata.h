#pragma once
#include <string>
#include "Question.h"
#include <vector>

struct SurveyMetadata
{
	// this will contain the name of the survey, the questions and answers (each question has 4 answers, with only one correct)
	std::string surveyName;
	std::vector<Question> questions;
};
