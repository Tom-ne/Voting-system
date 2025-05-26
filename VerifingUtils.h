#pragma once
#include <string>
#include "Sha256.h"
#include <vector>
#include <openssl/sha.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>

class VerifingUtils
{
public:
	static bool verifySignature(const std::string& publicKey, const std::string& publicKeyHash, const std::string& signature, const std::string& messageJson);

private:
	static std::string toHexString(const unsigned char* hash, size_t length);
	static std::string sha256Hex(const std::string& input);
	static bool checkKeyHash(const std::string& publicKey, const std::string& publicKeyHash);
	static std::vector<unsigned char> base64Decode(const std::string& input);

	static EVP_PKEY* loadPublicKeyFromString(const std::string& keyPem);
};
