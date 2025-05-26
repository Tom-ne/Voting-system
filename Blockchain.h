#pragma once
#include <vector>
#include "Block.h"

class Blockchain
{
public:
	Blockchain();

	void createBlock(std::unique_ptr<Response> response);
	bool isValid() const;

	const Block& getLastBlock() const;
	uint64_t getCurrentTimestamp() const;
private:
	std::vector<std::unique_ptr<Block>> blocks;
};

