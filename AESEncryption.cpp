#include "AESEncryption.hpp"


AESEncryption::AESEncryption()
{
	OpenSSL_add_all_algorithms();
}