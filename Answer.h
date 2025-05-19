#pragma once
#include <string>
#include <unordered_map>

class Answer
{
public:
    Answer(const std::string& surveyId, const std::string& userId, const std::uint64_t timestamp, const std::unordered_map<std::string, std::string>& answers, const std::string& signature);
    ~Answer();

    const std::string toJson() const;
    const std::unordered_map<std::string, std::string> toMap() const;
    const std::string answersToJson() const;
private:
    std::string surveyId;
    std::string userId;
    std::uint64_t timestamp;
    std::unordered_map<std::string, std::string> answers;
    std::string signature;
};
