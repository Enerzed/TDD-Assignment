#include <gtest/gtest.h>

#include "RSAEncryption.hpp"
#include "RSAEncryption.cpp"
#include "AESEncryption.hpp"
#include "AESEncryption.cpp"


/*
* RSA tests
*/

TEST(TestsRSA, ConstructorTest)
{
	RSAEncryption* rsa = new RSAEncryption();
	EXPECT_NE(rsa, nullptr);
}

TEST(TestsRSA, GenerateKeysTest)
{
	RSAEncryption* rsa = new RSAEncryption();

	rsa->GenerateKeys();

	EXPECT_NE(rsa->GetPublicKey(), "");
	EXPECT_NE(rsa->GetPrivateKey(), "");
}

TEST(TestsRSA, EncryptDecryptTest)
{
	RSAEncryption* rsa = new RSAEncryption();
	rsa->GenerateKeys();
	std::string message = "Hello World!";

	std::string encrypted = rsa->Encrypt(message);
	std::string decrypted = rsa->Decrypt(encrypted);

	EXPECT_EQ(message, decrypted);
}


/*
* AES tests
*/

TEST(TestsAES, ConstructorTest)
{
	AES* aes = new AES();
	EXPECT_NE(aes, nullptr);
}