#include <gtest/gtest.h>

#include "RSAEncryption.hpp"
#include "RSAEncryption.cpp"

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

	EXPECT_NE(rsa->GetPublicKey(), nullptr);
	EXPECT_NE(rsa->GetPrivateKey(), nullptr);
}