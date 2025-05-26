#include "Response.h"

Response::Response(const std::string& json)
{
	// Simple parsing logic, assuming the JSON format is always correct
	size_t qIdPos = json.find("\"questionId\":") + 14;
	size_t uIdPos = json.find("\"userId\":") + 10;
	size_t sOptPos = json.find("\"selectedOption\":") + 17;
	size_t pKeyPos = json.find("\"publicKey\":\"") + 14;
	timeTaken = json.find("\"timeTaken\":") + 13;

	questionId = std::stoi(json.substr(qIdPos, json.find(',', qIdPos) - qIdPos));
	userId = std::stoi(json.substr(uIdPos, json.find(',', uIdPos) - uIdPos));
	selectedOption = std::stoi(json.substr(sOptPos, json.find(',', sOptPos) - sOptPos));
	publicKey = json.substr(pKeyPos, json.find('"', pKeyPos) - pKeyPos);
}

std::string Response::toJson() const
{
return "{\"questionId\":" + std::to_string(questionId) +
		",\"userId\":" + std::to_string(userId) +
		",\"selectedOption\":" + std::to_string(selectedOption) +
		",\"publicKey\":\"" + publicKey + "\"}";
}
