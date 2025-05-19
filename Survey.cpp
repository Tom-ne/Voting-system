#include "Survey.h"
#include <chrono>
#include <stdexcept>

Survey::Survey(const std::string& surveyId, const std::string& title)
    : surveyId(surveyId), title(title)
{
    // Create the genesis block
    std::vector<Answer> emptyAnswers;
    std::string genesisHash = "0"; // No previous block
    std::string genesisSignature = ""; // No need to sign genesis
    std::uint64_t genesisTime = getCurrentTimestamp();

    blocks.push_back(std::make_unique<Block>(
        0,                         // index
        std::move(emptyAnswers),   // no answers
        genesisTime,               // current time
        genesisHash,               // "previous" hash
        genesisSignature           // no signature
    ));
}

void Survey::addAnswer(const Answer& answer)
{
    // Add the answer to the vector
    pendingAnswers.push_back(answer);

    // If the vector length is >= 10, create a block
    if (pendingAnswers.size() >= 10)
    {
        createBlock(""); // Signature can be added if needed
    }
}

void Survey::createBlock(const std::string& signature)
{
    const Block& previousBlock = getLatestBlock();
    std::uint64_t currentTime = getCurrentTimestamp();

    // Check timestamp sanity: must be strictly increasing
    if (currentTime < previousBlock.getTimestamp())
    {
        throw std::runtime_error("Block timestamp must be strictly greater than the previous block.");
    }

    // Create a new block with the pending answers and metadata
    blocks.push_back(std::make_unique<Block>(
        previousBlock.getIndex() + 1,
        std::move(pendingAnswers), // transfer ownership
        currentTime,
        previousBlock.getHash(),
        signature
    ));

    // No need to clear pendingAnswers; it was moved
}

bool Survey::verifyChain() const
{
    // Iterate through the blockchain, skipping the genesis block
    for (size_t i = 1; i < blocks.size(); ++i)
    {
        const Block& current = *blocks[i];
        const Block& previous = *blocks[i - 1];

        // Recompute and validate current block's hash
        if (current.getHash() != current.calculateHash())
        {
            return false;
        }

        // Check if the previous hash matches the actual hash of the previous block
        if (current.getPreviousHash() != previous.getHash())
        {
            return false;
        }
    }
    return true;
}

std::vector<Answer> Survey::getAnswers() const
{
    // Return all answers stored in all blocks + any pending answers
    std::vector<Answer> allAnswers;

    // Collect answers from all finalized blocks
    for (const auto& block : blocks)
    {
        const std::vector<Answer>& blockAnswers = block->getAnswers();
        allAnswers.insert(allAnswers.end(), blockAnswers.begin(), blockAnswers.end());
    }

    // Append pending answers that haven't been included in a block yet
    allAnswers.insert(allAnswers.end(), pendingAnswers.begin(), pendingAnswers.end());

    return allAnswers;
}

const std::string& Survey::getId() const
{
	return surveyId;
}

std::uint64_t Survey::getCurrentTimestamp() const
{
    // Return time since epoch in milliseconds
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

void Survey::addBlock(std::unique_ptr<Block> block)
{
    // Add a block directly to the chain (for testing purposes)
	if (block)
	{
		blocks.push_back(std::move(block));
	}
	else
	{
		throw std::invalid_argument("Block cannot be null.");
	}
}

const Block& Survey::getLatestBlock() const
{
    // Return a reference to the last block in the chain
    return *blocks.back();
}
