#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Answer.h"

class Block
{
public:
	Block(int index, std::vector<Answer> answers, const std::uint64_t timestamp, const std::string& previousHash, const std::string& signature);

	const std::string calculateHash() const;
	const int getIndex() const;
	const std::uint64_t getTimestamp() const;
	const std::vector<Answer>& getAnswers() const;
	const std::string& getHash() const;
	const std::string& getPreviousHash() const;
private:
	int index;
	std::vector<Answer> answers;
	std::uint64_t timestamp;
	std::string previousHash;
	std::string signature;
	std::string hash;
};

