#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cstdint>
#include "Answer.h"
#include "Block.h"

class Survey
{
public:
    Survey(const std::string& surveyId, const std::string& title);
    ~Survey() = default;

    void addAnswer(const Answer& answer);
    void createBlock(const std::string& signature);
    bool verifyChain() const;
    std::vector<Answer> getAnswers() const;
    const std::string& getId() const;
    std::uint64_t getCurrentTimestamp() const;

    // temperary method to add a block directly
    void addBlock(std::unique_ptr<Block> block);

    const Block& getLatestBlock() const;
private:
    std::string surveyId;
    std::string title;
    std::vector<Answer> pendingAnswers;
    std::vector<std::unique_ptr<Block>> blocks;

};
