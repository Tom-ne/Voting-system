#define _CRT_SECURE_NO_WARNINGS

#include "VerifingUtils.h"
#include <openssl/applink.c>

bool VerifingUtils::verifySignature(const std::string& publicKey, const std::string& publicKeyHash, const std::string& signature, const std::string& messageJson)
{
	if (!checkKeyHash(publicKey, publicKeyHash)) {
		return false;
	}

	EVP_PKEY* pubKey = loadPublicKeyFromString(publicKey);
	if (!pubKey) {
		std::cerr << "Failed to load public key from string." << std::endl;
		return false;
	}

	std::vector<unsigned char> decodedSignature = base64Decode(signature);
	if (decodedSignature.empty()) {
		std::cerr << "Failed to decode base64 signature." << std::endl;
		EVP_PKEY_free(pubKey);
		return false;
	}

	EVP_MD_CTX* ctx = EVP_MD_CTX_new();
	if (!ctx) {
		std::cerr << "Failed to create EVP_MD_CTX." << std::endl;
		EVP_PKEY_free(pubKey);
		return false;
	}

	bool result = false;

	if (EVP_DigestVerifyInit(ctx, nullptr, EVP_sha256(), nullptr, pubKey) != 1) {
		std::cerr << "EVP_DigestVerifyInit failed." << std::endl;
		EVP_MD_CTX_free(ctx);
		EVP_PKEY_free(pubKey);
		return false;
	}

	if (EVP_DigestVerifyUpdate(ctx, messageJson.c_str(), messageJson.size()) != 1) {
		std::cerr << "EVP_DigestVerifyUpdate failed." << std::endl;
		EVP_MD_CTX_free(ctx);
		EVP_PKEY_free(pubKey);
		return false;
	}

	if (EVP_DigestVerifyFinal(ctx, decodedSignature.data(), decodedSignature.size()) == 1) {
		result = true;
	}
	else {
		std::cerr << "EVP_DigestVerifyFinal failed." << std::endl;
	}

	EVP_MD_CTX_free(ctx);
	EVP_PKEY_free(pubKey);
	return result;
}

std::string VerifingUtils::toHexString(const unsigned char* hash, size_t length)
{
	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for (size_t i = 0; i < length; ++i) {
		ss << std::setw(2) << static_cast<int>(hash[i]);
	}
	return ss.str();
}

std::string VerifingUtils::sha256Hex(const std::string& input)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
	return toHexString(hash, SHA256_DIGEST_LENGTH);
}

bool VerifingUtils::checkKeyHash(const std::string& publicKey, const std::string& publicKeyHash)
{
	std::string hashedKey = sha256Hex(publicKey);

	if (hashedKey == publicKeyHash) {
		return true;
	} else {
		std::cerr << "Public key hash mismatch. Expected: " << publicKeyHash << ", got: " << hashedKey << std::endl;
		return false;
	}
}

std::vector<unsigned char> VerifingUtils::base64Decode(const std::string& input)
{
	BIO* bio = BIO_new_mem_buf(input.data(), static_cast<int>(input.size()));
	BIO* b64 = BIO_new(BIO_f_base64());

	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

	bio = BIO_push(b64, bio);

	std::vector<unsigned char> decoded(input.size());
	int decodedLength = BIO_read(bio, decoded.data(), static_cast<int>(decoded.size()));

	if (decodedLength <= 0) {
		std::cerr << "Base64 decoding failed." << std::endl;
		BIO_free_all(bio);
		return {};
	}
	else {
		decoded.resize(decodedLength);
	}

	BIO_free_all(bio);
	return decoded;
}

EVP_PKEY* VerifingUtils::loadPublicKeyFromString(const std::string& keyPem)
{
	BIO* bio = BIO_new_mem_buf(keyPem.data(), static_cast<int>(keyPem.size()));
	if (!bio) {
		std::cerr << "Failed to create BIO for public key." << std::endl;
		return nullptr;
	}
	EVP_PKEY* pkey = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
	BIO_free(bio);

	if (!pkey) {
		std::cerr << "Failed to read public key from PEM." << std::endl;
		ERR_print_errors_fp(stderr);
		return nullptr;
	}

	return pkey;
}
