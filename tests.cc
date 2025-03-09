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