#include "Block.h"
#include "SHA256.h"

Block::Block(int index, std::vector<Answer> answers, const std::uint64_t timestamp, const std::string& previousHash, const std::string& signature)
{
	this->index = index;
	this->answers = std::move(answers);
	this->timestamp = timestamp;
	this->previousHash = previousHash;
	this->signature = signature;
	this->hash = calculateHash();
}

const std::string Block::calculateHash() const
{
	// step 1: create the block string
	// the block string is the following format: {"index": <index>, "answers": [<answers>], "timestamp": <timestamp>, "previousHash": <previousHash>, "signature": <signature>}
	std::string blockString = "{\"index\":" + std::to_string(index) + ",\"answers\":[";
	for (size_t i = 0; i < answers.size(); i++)
	{
		blockString += answers[i].toJson();
		if (i != answers.size() - 1)
		{
			blockString += ",";
		}
	}
	blockString += "],\"timestamp\":" + std::to_string(timestamp) + ",\"previousHash\":\"" + previousHash + "\",\"signature\":\"" + signature + "\"}";

	// step 2: use SHA256 to hash the block string
	SHA256 sha256;
	sha256.update(blockString);
	return SHA256::toString(sha256.digest());
}

const int Block::getIndex() const
{
	return this->index;
}

const std::uint64_t Block::getTimestamp() const
{
	return this->timestamp;
}

const std::vector<Answer>& Block::getAnswers() const
{
	return this->answers;
}

const std::string& Block::getHash() const
{
	return this->hash;
}

const std::string& Block::getPreviousHash() const
{
	return this->previousHash;
}
