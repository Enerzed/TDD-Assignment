#include "RSAEncryption.hpp"


RSAEncryption::RSAEncryption()
{
    OpenSSL_add_all_algorithms();
}

void RSAEncryption::GenerateKeys()
{
    //Генерируем ключи RSA
    RSA* rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    // Переводим публичный ключ в формат PEM, из него уже можно перевести в строчный
    BIO* publicKeyBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(publicKeyBio, rsa);
    char* publicKeyBuffer;
    long publicKeyLength = BIO_get_mem_data(publicKeyBio, &publicKeyBuffer);
    public_key = std::string(publicKeyBuffer, publicKeyLength);
    BIO_free(publicKeyBio);
    // Переводим приватный ключ в формат PEM, из него уже можно перевести в строчный
    BIO* privateKeyBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(privateKeyBio, rsa, NULL, NULL, 0, NULL, NULL);
    char* privateKeyBuffer;
    long privateKeyLength = BIO_get_mem_data(privateKeyBio, &privateKeyBuffer);
    private_key = std::string(privateKeyBuffer, privateKeyLength);
    BIO_free(privateKeyBio);
    // Освобождаем контекст
    RSA_free(rsa);
}

std::string RSAEncryption::Encrypt(std::string plaintext)
{
    // Создаем контекст для RSA
    RSA* rsa = RSA_new();
    BIO* bio = BIO_new_mem_buf(public_key.c_str(), -1);
    PEM_read_bio_RSAPublicKey(bio, &rsa, NULL, NULL);
    BIO_free(bio);
    // Зашифровываем
    int maxLength = RSA_size(rsa);
    std::string ciphertext;

    ciphertext.resize(maxLength);
    int ciphertextLength = RSA_public_encrypt(plaintext.length(), reinterpret_cast<const unsigned char*>(plaintext.c_str()), reinterpret_cast<unsigned char*>(&ciphertext[0]), rsa, RSA_PKCS1_PADDING);
    ciphertext.resize(ciphertextLength);
    // Освобождаем контекст и возвращаем шифротекст
    RSA_free(rsa);
    return ciphertext;
}

std::string RSAEncryption::Decrypt(std::string ciphertext)
{
    // Создаем контекст для RSA
    RSA* rsa = RSA_new();
    BIO* bio = BIO_new_mem_buf(private_key.c_str(), -1);
    PEM_read_bio_RSAPrivateKey(bio, &rsa, NULL, NULL);
    BIO_free(bio);
    // Расшифровываем
    int maxLength = RSA_size(rsa);
    std::string plaintext;

    plaintext.resize(maxLength);
    int plaintextLength = RSA_private_decrypt(ciphertext.length(), reinterpret_cast<const unsigned char*>(ciphertext.c_str()), reinterpret_cast<unsigned char*>(&plaintext[0]), rsa, RSA_PKCS1_PADDING);
    plaintext.resize(plaintextLength);
    // Освобождаем контекст и возвращаем чистый текст
    RSA_free(rsa);
    return plaintext;
}

std::string RSAEncryption::GetPublicKey()
{
    return public_key;
}

std::string RSAEncryption::GetPrivateKey()
{
    return private_key;
}