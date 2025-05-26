#include "Blockchain.h"
#include <stdexcept>
#include <chrono>
#include <iostream>

Blockchain::Blockchain()
{
	// create the genesis block
	auto genesisResponse = std::make_unique<Response>(0, 0, 0, "gensis", 0);
	this->blocks.push_back(std::make_unique<Block>(genesisResponse));
}

void Blockchain::createBlock(std::unique_ptr<Response> response)
{
	const Block& previousBlock = this->getLastBlock();
	std::uint64_t currentTime = getCurrentTimestamp();

	if (currentTime < previousBlock.getTimestamp()) {
		throw std::runtime_error("Current timestamp is less than the last block's timestamp.");
	}

	auto newBlock = std::make_unique<Block>(response, previousBlock.hash());
	newBlock->setTimestamp(currentTime);
	this->blocks.push_back(std::move(newBlock));
}

bool Blockchain::isValid() const
{
	for (size_t i = 1; i < blocks.size(); ++i) {
		const Block& currentBlock = *blocks[i];
		const Block& previousBlock = *blocks[i - 1];

		if (currentBlock.getPreviousHash() != previousBlock.hash())
		{
			return false; // Hash mismatch indicates tampering
		}

		if (currentBlock.getTimestamp() < previousBlock.getTimestamp())
		{
			return false;
		}
	}
		return true;
}

const Block& Blockchain::getLastBlock() const
{
	if (this->blocks.empty()) {
		throw std::runtime_error("Blockchain is empty, no last block available.");
	}
	return *this->blocks.back();
}

uint64_t Blockchain::getCurrentTimestamp() const
{
	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}
