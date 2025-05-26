#pragma once
#include <string>
#include <array>

class Question
{
public:
	Question(unsigned int id, const std::string& text, const std::array<std::string, 4>& options, unsigned int correctIndex);

	std::string toJson() const;
	static Question fromJson(const std::string& jsonStr);

	const std::string& getText();
	const std::array<std::string, 4>& getAnswers() const;
	unsigned int getCorrectAnswerIndex() const;
	unsigned int getId() const;

private:
	unsigned int id;
	std::string text;
	std::array<std::string, 4> answers;
	unsigned int correctAnswerIndex;
};

