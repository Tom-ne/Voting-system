#include "Survey.h"
#include "Answer.h"
#include <iostream>

int main() {
	Survey survey("survery123", "User Feedback");
	
	// simulate 15 answers
	for (int i = 0; i < 15; ++i) {
		std::unordered_map<std::string, std::string> answers = {
			{"Q1", "Yes"},
			{"Q2", "No"},
		};

		Answer answer(survey.getId(), "user" + std::to_string(i), survey.getCurrentTimestamp(), answers, "signature" + std::to_string(i));
		survey.addAnswer(answer);
	}

	if (survey.verifyChain()) {
		std::cout << "Blockchain is valid." << std::endl;
	} else {
		std::cout << "Blockchain is invalid." << std::endl;
	}

	auto allAnswers = survey.getAnswers();
	std::cout << "Collected " << allAnswers.size() << " answers." << std::endl;

	Block block = survey.getLatestBlock();
	// print the content of the block
	std::cout << "Block hash: " << block.getHash() << std::endl;
	std::cout << "Previous block hash: " << block.getPreviousHash() << std::endl;
	std::cout << "Timestamp: " << block.getTimestamp() << std::endl;

	return 0;
}