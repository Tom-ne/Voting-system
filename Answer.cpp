#include "Answer.h"

Answer::Answer(const std::string& surveyId, const std::string& userId, const std::uint64_t timestamp, const std::unordered_map<std::string, std::string>& answers, const std::string& signature)
{
	this->surveyId = surveyId;
	this->userId = userId;
	this->timestamp = timestamp;
	this->answers = answers;
	this->signature = signature;
}

Answer::~Answer()
{
}

const std::string Answer::toJson() const
{
	return "{\"surveyId\":\"" + surveyId + "\",\"userId\":\"" + userId + "\",\"timestamp\":\"" + std::to_string(timestamp) + "\",\"answers\":{" + answersToJson() + "},\"signature\":\"" + signature + "\"}";
}

const std::unordered_map<std::string, std::string> Answer::toMap() const
{
	std::unordered_map<std::string, std::string> map;
	map["surveyId"] = surveyId;
	map["userId"] = userId;
	map["timestamp"] = timestamp;
	for (const auto& answer : answers)
	{
		map[answer.first] = answer.second;
	}
	map["signature"] = signature;
	return map;
}

const std::string Answer::answersToJson() const
{
	std::string json;
	bool first = true;
	for (const auto& [key, value] : answers)
	{
		if (!first) json += ",";
		json += "\"" + key + "\":\"" + value + "\"";
		first = false;
	}
	return json;
}

