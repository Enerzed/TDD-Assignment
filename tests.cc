#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

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
	AESEncryption* aes = new AESEncryption();
	EXPECT_NE(aes, nullptr);
}

TEST(TestsAES, GenerateKeyAndIV)
{
	AESEncryption* aes = new AESEncryption();

	aes->GenerateKeyAndIV();

	EXPECT_NE(aes->GetKey(), "");
	EXPECT_NE(aes->GetIV(), "");
}

TEST(TestsAES, EncryptDecryptTest)
{
	AESEncryption* aes = new AESEncryption();
	aes->GenerateKeyAndIV();
	std::string message = "Hello World!";

	std::string encrypted = aes->Encrypt(message);
	std::string decrypted = aes->Decrypt(encrypted);

	EXPECT_EQ(message, decrypted);
}

/*
* FileManager tests
*/

namespace fs = std::filesystem;

class FileManagerTest : public::testing::Test
{
protected:
	void SetUp() override
	{
		test_folder = fs::temp_directory_path() / "FileManagerTest";
		fs::create_directory(test_folder);

		test_file_path = test_folder / "test.txt";
		std::ofstream test_file(test_file_path);
		test_file << "hello world!";
		test_file.close();
	}

	void TearDown() override
	{
		fs::remove_all(test_folder);
	}

	fs::path test_folder;
	fs::path test_file_path;
};

TEST_F(FileManagerTest, EncryptDecryptAllFiles)
{
	FileManager file_manager(test_folder.string());

	file_manager.EncryptAllFiles();

	std::ifstream encrypted_file(test_file_path);
	std::string encrypted_content((std::istreambuf_iterator<char>(encrypted_file)), std::istreambuf_iterator<char>());
	encrypted_file.close();
	EXPECT_NE(encrypted_content, "hello world!");

	file_manager.DecryptAllFiles();

	std::ifstream decrypted_file(test_file_path);
	std::string decrypted_content((std::istreambuf_iterator<char>(decrypted_file)), std::istreambuf_iterator<char>());
	decrypted_file.close();
	EXPECT_EQ(decrypted_content, "hello world!");
}