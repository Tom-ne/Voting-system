#pragma once
#include <string>
#include "Sha256.h"
#include <vector>

class VerifingUtils
{
public:
	static bool verifySignature(const std::string& publicKey, const std::string& publicKeyHash, const std::string& signature, const std::string& messageJson);

private:
	static bool rsaVerifySignature(const std::string& publicKey, const std::string& signature, const std::string& messageJson);
};
