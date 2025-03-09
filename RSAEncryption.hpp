#pragma once

#include <iostream>

#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/rand.h>


class RSAEncryption
{
private:
	std::string private_key;
	std::string public_key;
	
public:
	RSAEncryption();
	
	void GenerateKeys();

	std::string GetPublicKey();
	std::string GetPrivateKey();
	// todo add encrypt/decrypt methods
};