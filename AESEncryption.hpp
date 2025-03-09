#pragma once

#include <iostream>

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/pem.h>
#include <openssl/rand.h>


class AESEncryption
{
private:
	const EVP_CIPHER* cipher;
	std::string key, iv;
public:
	AESEncryption();
	
	void GenerateKeyAndIV();

	std::string Encrypt(std::string);
	std::string Decrypt(std::string);

	// todo set methods

	std::string GetKey();
	std::string GetIV();
};