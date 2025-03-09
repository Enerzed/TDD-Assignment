#include "AESEncryption.hpp"


AESEncryption::AESEncryption()
{
	OpenSSL_add_all_algorithms();
    cipher = EVP_get_cipherbyname("aes-256-cbc");
    if (!cipher)
    {
        throw std::runtime_error("Error: AES-256-CBC cipher not found.");
    }
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

std::string AESEncryption::Encrypt(std::string plaintext)
{
    // Создаем контекст
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(ctx);
    // Зашифровываем
    EVP_EncryptInit_ex(ctx, cipher, nullptr, reinterpret_cast<const unsigned char*>(key.c_str()), (unsigned char*)iv.c_str());

    int len = 0, ciphertext_len = 0;
    int plaintext_len = plaintext.length();

    std::string ciphertext(plaintext_len + EVP_CIPHER_block_size(cipher), '\0');
    unsigned char* ciphertext_ptr = reinterpret_cast<unsigned char*>(&ciphertext[0]);

    EVP_EncryptUpdate(ctx, ciphertext_ptr, &len, reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext_len);
    ciphertext_len += len;

    EVP_EncryptFinal_ex(ctx, ciphertext_ptr + len, &len);
    ciphertext_len += len;
    // Освобождаем контекст
    EVP_CIPHER_CTX_free(ctx);
    return ciphertext.substr(0, ciphertext_len);
}

std::string AESEncryption::Decrypt(std::string ciphertext)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(ctx);
    // Расшифровываем
    EVP_DecryptInit_ex(ctx, cipher, nullptr, reinterpret_cast<const unsigned char*>(key.c_str()), (unsigned char*)iv.c_str());

    int len = 0, plaintext_len = 0;
    int ciphertext_len = ciphertext.length();

    std::string plaintext(ciphertext_len, '\0');
    unsigned char* plaintext_ptr = reinterpret_cast<unsigned char*>(&plaintext[0]);

    EVP_DecryptUpdate(ctx, plaintext_ptr, &len, reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext_len);
    plaintext_len += len;

    EVP_DecryptFinal_ex(ctx, plaintext_ptr + len, &len);
    plaintext_len += len;
    // Освобождаем контекст
    EVP_CIPHER_CTX_free(ctx);
    return plaintext.substr(0, plaintext_len);
}

std::string AESEncryption::GetKey()
{
	return key;
}

std::string AESEncryption::GetIV()
{
	return iv;
}