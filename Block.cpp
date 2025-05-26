#include "Block.h"
#include "SHA256.h"

Block::Block(std::unique_ptr<Response>& response) : response(*response), timestamp(0), previousHash("")
{
}

Block::Block(std::unique_ptr<Response>& response, const std::string previousHash) : response(*response), timestamp(0), previousHash(previousHash)
{
}

void Block::setTimestamp(uint64_t timestamp)
{
	this->timestamp = timestamp;
}

const std::string Block::hash() const
{
	// the hash of the block is made from the json of the response, the timestamp and the previous hash
	std::string blockData = this->response.toJson() + std::to_string(this->timestamp) + this->previousHash;
	SHA256 sha256;
	sha256.update(blockData);
	return SHA256::toString(sha256.digest());
}

uint64_t Block::getTimestamp() const
{
	return this->timestamp;
}

std::string Block::getPreviousHash() const
{
	return this->previousHash;
}
