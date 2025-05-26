#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <bitset>
#include <map>
#include <iostream>
#include "SHA256.h"

// Base64 encoding (manual)
std::string base64Encode(const std::vector<unsigned char>& data) {
	static const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	std::string encoded;
	int val = 0, valb = -6;
	for (unsigned char c : data) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			encoded.push_back(table[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}
	if (valb > -6) encoded.push_back(table[((val << 8) >> (valb + 8)) & 0x3F]);
	while (encoded.size() % 4) encoded.push_back('=');
	return encoded;
}

// Serialize number into big-endian byte array
std::vector<unsigned char> serializeBigEndian(unsigned long long num) {
	std::vector<unsigned char> bytes;
	while (num > 0) {
		bytes.insert(bytes.begin(), static_cast<unsigned char>(num & 0xFF));
		num >>= 8;
	}
	if (bytes.empty()) bytes.push_back(0); // to handle 0
	return bytes;
}

// Encode (n, e) as base64
std::string encodePublicKeyBase64(long long n, int e) {
	std::vector<unsigned char> serialized;

	auto nBytes = serializeBigEndian(n);
	auto eBytes = serializeBigEndian(e);

	// Add 2 bytes for each length prefix
	serialized.push_back(nBytes.size());
	serialized.insert(serialized.end(), nBytes.begin(), nBytes.end());

	serialized.push_back(eBytes.size());
	serialized.insert(serialized.end(), eBytes.begin(), eBytes.end());

	return base64Encode(serialized);
}

int main() {
	// step 1: selecting two large prime numbers
	int p = 61;
	int q = 53;

	// step 2: compute n = p * q
	long long n = p * q;

	// step 3: compute phi(n)
	long long phi = (p -1 ) * (q - 1);

	// step 4: choose the public exponent e
	int e = 17; // e must be coprime to phi(n) and 1 < e < phi(n)

	// step 5: compute the private exponent d
	int d = 0;
	// d = (1 mod phi(n)) / e
	for (int i = 1; i < phi; ++i) {
		if ((e * i) % phi == 1) {
			d = i;
			break;
		}
	}

	std::cout << "d is " << d << std::endl;

	// Keys
	// public key is (n, e)
	// private key is (n, d)
	std::cout << "Public Key: (" << n << ", " << e << ")" << std::endl;
	std::cout << "Public Key Base64: " << encodePublicKeyBase64(n, e) << std::endl;
	std::cout << "Private Key: (" << n << ", " << d << ")" << std::endl;
	std::cout << "Private Key Base64: " << encodePublicKeyBase64(n, d) << std::endl;
	
	// Signning a message
	std::string message = "Hello, RSA!";
	// step 1: compute the hash of the message
	SHA256 sha256;
	sha256.update(message);
	std::string messageHash = SHA256::toString(sha256.digest());

	// step 2: create the signature
	// s = (hash(message) ^ d) mod n
	long long signature = 1;
	for (char c : messageHash) {
		signature = (signature * c) % n;
	}

	std::cout << "Signature: " << signature << std::endl;

	// Verifying the signature
	// decrypt signature using the public key
	long long decryptedSignature = 1;
	for (char c : messageHash) {
		decryptedSignature = (decryptedSignature * c) % n;
	}

	if (decryptedSignature == signature) {
		std::cout << "Signature is valid." << std::endl;
	} else {
		std::cout << "Signature is invalid." << std::endl;
	}

	return 0;
}
