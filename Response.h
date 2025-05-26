#pragma once
#include <string>

class Response
{
public:
	Response(unsigned int questionId, unsigned int userId, unsigned int selectedOption, const std::string& publicKey, unsigned int timeTaken)
		: questionId(questionId), userId(userId), selectedOption(selectedOption), publicKey(publicKey), timeTaken(timeTaken) {}

	Response(const std::string& json);

	std::string toJson() const;
private:
	unsigned int questionId;
	unsigned int userId;
	unsigned int selectedOption;
	unsigned int timeTaken; // in seconds
	std::string publicKey;
};
