#include <gtest/gtest.h>


/*
* RSA tests
*/

TEST(TestsRSA, ConstructorTest)
{
	RSAEncryption* rsa = new RSAEncryption();
	EXPECT_NE(rsa, nullptr);
}