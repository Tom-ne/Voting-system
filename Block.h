#pragma once
#include "Response.h"
#include <memory>

class Block
{
public:
	Block(std::unique_ptr<Response>& response);
	Block(std::unique_ptr<Response>& response, const std::string previousHash);

	void setTimestamp(uint64_t timestamp);
	const std::string hash() const;
	uint64_t getTimestamp() const;

	std::string getPreviousHash() const;
private:
	Response response;
	uint64_t timestamp;
	std::string previousHash;
};

