#include "ResponseManager.h"

bool ResponseManager::isValidResponse(const std::shared_ptr<Response>& response, const std::string& publicKeyPem, const std::string& hash, const std::string& signature)
{
	if (!response) {
		return false;
	}
	return VerifingUtils::verifySignature(publicKeyPem, hash, signature, response->toJson());
}
