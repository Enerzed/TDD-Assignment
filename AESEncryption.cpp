#include "AESEncryption.hpp"


AESEncryption::AESEncryption()
{
	OpenSSL_add_all_algorithms();
}

void AESEncryption::GenerateKeyAndIV()
{
    unsigned char newKey[32];
    if (RAND_bytes(newKey, sizeof(newKey)) != 1)
        throw std::runtime_error("Error generating random key");
    key = (reinterpret_cast<const char*>(newKey));

    unsigned char newIV[16];
    if (RAND_bytes(newIV, sizeof(newIV)) != 1)
        throw std::runtime_error("Error generating random IV");
    iv = (reinterpret_cast<const char*>(newIV));
}

std::string AESEncryption::GetKey()
{
	return key;
}

std::string AESEncryption::GetIV()
{
	return iv;
}