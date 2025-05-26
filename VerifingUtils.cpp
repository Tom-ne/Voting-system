#include "VerifingUtils.h"

bool VerifingUtils::verifySignature(const std::string& publicKey, const std::string& publicKeyHash, const std::string& signature, const std::string& messageJson)
{
	std::string expectedHash = publicKeyHash;
	SHA256 sha256;
	sha256.update(publicKey);
	std::string publicKeyHashComputed = SHA256::toString(sha256.digest());

	if (expectedHash != publicKeyHashComputed) {
		return false; // Public key hash does not match
	}

	return rsaVerifySignature(publicKey, signature, messageJson);
}

bool VerifingUtils::rsaVerifySignature(const std::string& publicKey, const std::string& signature, const std::string& messageJson)
{
	return false;
}
