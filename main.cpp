#include "VerifingUtils.h"

int main() {
	std::string signature = "CVoq3r8SSx43sQ6Un8kB974yP7mBoiNPRVvhZ4ZcJG9vh34x+f/gqiRIC/66WUSfLiePbcOLFscutvb6C73t7bJqoxnMkw5BbB9kSidL4i5Yt6ygY+g6ldCX0BGTp8FfZFxaJR+E6OZOW/QhXWTorpAw8gLUxh+EHglpvwlSzOObrtfQrFygZcF1I7pSGvvU+ddmfrWU+J7986kN/Yd/68J8jngVNv5RgeuUqduIKENv0wpiiyG6rYSpHRLDAzbAmKVq8wJuv6YwzjC6DwNpQsM9RsptHLBcgWgjYB3FWuoU3fR2IZRDu/oC6wkQoYCoku9hAu/krFFwLcmQ9v2P2w==";
	std::string publicKeyPem = R"(-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEArG84hTVs5k9597cRti+X
+VmbbRLkeVsqbF/ky5MEaRrviSZIxBrIsc1IWkyvMlF7lrpZnTda3H0MbvpfXBGK
ZWzbNlH3qlNceaRcNlPockqev+Ihqzbx0Pi16j5LeyFK0K4ZHY/PGjQWtEV6kSSF
7QRoBbxIWGXZX4hhS4K9X9sHj2Dt8+F3YsiNk6cC8Jr1nJIHHjaYbw9iwUyA80jD
B0QN6otqI40rgYRXhRm9QojefNEMUFb5/RglsOVi5fQm13KNj5XhnQciazmCQiQT
a/58aQFOkaI5Bl0676l2wkxhU8p1Pf5n3V7rAfnLM2iHATUpPOqtkjgBb+5LNNsu
3wIDAQAB
-----END PUBLIC KEY-----)";
	std::string hash = "f6b85334fe0da6cd9027a2b76eb2b26a8ffe50a4974c4437af3cb6bba730ddda";
	if (VerifingUtils::verifySignature(publicKeyPem, hash, signature, "Hello, RSA!")) {
		std::cout << "Signature is valid." << std::endl;
	} else {
		std::cout << "Signature is invalid." << std::endl;
	}

	return 0;
}