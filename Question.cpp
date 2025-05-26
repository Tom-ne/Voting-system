#include "Question.h"
#include "json.hpp"

using json = nlohmann::json;

Question::Question(unsigned int id, const std::string& text, const std::array<std::string, 4>& options, unsigned int correctIndex) : 
	id(id), text(text), answers(options), correctAnswerIndex(correctIndex) 
{
}

std::string Question::toJson() const
{
    json j;
    j["id"] = id;
    j["text"] = text;
    j["answers"] = answers;
    j["correctAnswerIndex"] = correctAnswerIndex;
    return j.dump();
}

Question Question::fromJson(const std::string& jsonStr)
{
    json j = json::parse(jsonStr);

    unsigned int id = j.at("id").get<unsigned int>();
    std::string text = j.at("text").get<std::string>();
    std::array<std::string, 4> answers;

    auto jAnswers = j.at("answers");
    if (jAnswers.size() != 4)
        throw std::runtime_error("Answers array must contain exactly 4 elements.");

    for (int i = 0; i < 4; ++i)
        answers[i] = jAnswers.at(i).get<std::string>();

    unsigned int correctIndex = j.at("correctAnswerIndex").get<unsigned int>();

    if (correctIndex > 3)
        throw std::runtime_error("correctAnswerIndex must be between 0 and 3.");

    return Question(id, text, answers, correctIndex);
}

const std::string& Question::getText()
{
    return text;
}

const std::array<std::string, 4>& Question::getAnswers() const
{
    return answers;
}

unsigned int Question::getCorrectAnswerIndex() const
{
    return correctAnswerIndex;
}

unsigned int Question::getId() const
{
    return id;
}


