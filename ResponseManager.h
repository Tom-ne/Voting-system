#pragma once
#include <memory>
#include "Response.h"
#include "VerifingUtils.h"

class ResponseManager
{
public:
	static bool isValidResponse(const std::shared_ptr<Response>& response, const std::string& publicKeyPem, const std::string& hash, const std::string& signature);
};
